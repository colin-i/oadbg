
format elfobj64

const NULL=0

const FALSE=0

#const EXIT_FAILURE=1

importx "gtk_application_window_new" gtk_application_window_new
importx "gtk_window_set_title" gtk_window_set_title
importx "gtk_widget_show" gtk_widget_show
importx "gtk_window_maximize" gtk_window_maximize

valuex window#1

functionx activate(sd app)
	setcall main.window gtk_application_window_new(app)
	sd id
	sd pth;setcall pth pthread_create(#id,(NULL),waiter) #,(NULL))
	if pth==0
		call gtk_window_set_title(main.window,"O ActionSWF Debugger")
		#k.g_signal_connect_data (window, b"close-request", closing, None, None, 0)
		call gtk_window_maximize(main.window)
		call gtk_widget_show(main.window)
		#k.gtk_test_widget_wait_for_draw(window)
	endif
endfunction

importx "gtk_application_new" gtk_application_new
importx "g_signal_connect_data" g_signal_connect_data
importx "g_application_run" g_application_run
importx "g_object_unref" g_object_unref

importx "pthread_create" pthread_create

importx "gtk_window_close" gtk_window_close
importx "g_idle_add" g_idle_add

importx "read" read
importx "write" write
importx "stdin" stdin
importx "stdout" stdout
importx "fileno" fileno

#If the function returns FALSE it is automatically removed from the list of event sources and will not be called again.
function closing(sd *arg)
	call gtk_window_close(main.window)
	return (FALSE)
endfunction

#void*
function waiter(sd *unused)
	datax len#1
	charsx buf#100
	sv i^stdin
	setcall i fileno(i#)
	sv j^stdout
	setcall j fileno(j#)

	importx "open" open
	sd f
	setcall f open("/home/bc/b/1",1)

	while 1==1
#it's not working on terminal (tested with echo -en "\x07\x00\x00\x00\"close\"" | edb --run ./oadbg | hexdump -C) when read is non-blocking anyway
#echo -en "\x07\x00\x00\x00\"close\"" | hexdump -C
#const F_SETFL=4
#importx "fcntl" fcntl
#call fcntl(i,(F_SETFL),0)  #causes read to block until new characters are present
		call read(i,#len,4)
		call read(i,#buf,len)

		sd out=4
		add out len
		call write(j,#len,out)

		call write(f,#len,out)

		datax len2#1
		charsx buf2#200

		importx "sprintf" sprintf
		importx "strlen" strlen
		set out 4
		addcall out sprintf(#buf2,"%u",len)
		setcall len2 strlen(#buf2)
		call write(j,#len2,out)

		importx "strcmp" strcmp
		sd cmp
		vstr qw="{\"a\":\"close\"}"
		setcall cmp strcmp(qw,#buf)
		if cmp==0
			call g_idle_add(closing) #,arg
			break
		endif

#		set len2 0
#		ss tmp;set tmp #buf
#		ss tmp2;set tmp2 #buf2
#		while len>0
#			sd n
#			setcall n sprintf(tmp2," %x",tmp#)
#			add len2 n
#			add tmp2 n
#			inc tmp
#			dec len
#		endwhile
#		set out 4
#		add out len2
#		call write(j,#len2,out)
#		call write(f,#len2,out)

		#call fflush(stdout#)
	endwhile
endfunction

entry main()
	sd a;setcall a gtk_application_new((NULL),0)
	call g_signal_connect_data(a,"activate",activate,(NULL),(NULL),0)
	sd r;setcall r g_application_run(a,0,(NULL))
	call g_object_unref(a)
	return r
