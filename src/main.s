
format elfobj64

const NULL=0

#function closing
#	return (FALSE)

importx "gtk_application_window_new" gtk_application_window_new
importx "gtk_window_set_title" gtk_window_set_title
importx "gtk_widget_show" gtk_widget_show
importx "gtk_window_maximize" gtk_window_maximize

functionx activate(sd app)
	sd window
	setcall window gtk_application_window_new(app)
	call gtk_window_set_title(window,"O Actionswf Debugger")
	#k.g_signal_connect_data (window, b"close-request", closing, None, None, 0)
	call gtk_window_maximize(window)
	call gtk_widget_show(window)
	#k.gtk_test_widget_wait_for_draw(window)
endfunction

importx "gtk_application_new" gtk_application_new
importx "g_signal_connect_data" g_signal_connect_data
importx "g_application_run" g_application_run
importx "g_object_unref" g_object_unref

entry main()
	sd a;setcall a gtk_application_new((NULL),0)
	call g_signal_connect_data(a,"activate",activate,(NULL),(NULL),0)
	sd r;setcall r g_application_run(a,0,(NULL))
	call g_object_unref(a)
	return r
