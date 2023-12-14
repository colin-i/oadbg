
ifndef OCOMP
OCOMP=o
endif
ifndef OLINK
OLINK=ounused
endif
ifndef OCONV
OCONV=otoc
endif
ifndef linkerflags
linkerflags=-O1 -s
endif

OFLAGS=x_file 2

all: oadbg

oadbg: main.o
	${OLINK} main.s.log
	@echo
	$(CC) ${linkerflags} $< -o oadbg `pkg-config --libs gtk4`

%.o: %.s
	${OCOMP} $< ${OFLAGS}
	${OCONV} $<.x
	$(CC) -c $*.c

clean:
	-rm main.o
	-rm main.s.log
	-rm main.s.x
	-rm main.c
	-rm oadbg
