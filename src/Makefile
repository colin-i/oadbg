
ifndef OCOMP
OCOMP=o
endif

ifndef OLINK
OLINK=ounused
endif

ifndef syms
syms=-s
endif

syms=-s

all: oadbg

oadbg: main.o
	${OLINK} main.s.log
	@echo
	$(CC) ${syms} main.o -o oadbg `pkg-config --libs gtk4`

%.o: %.s
	${OCOMP} $<

clean:
	-rm main.o
	-rm main.s.log
	-rm oadbg
