
syms=-s

all: oadbg a.out

a.out:
	cc test.c

oadbg: main.o
	ounused main.s.log
	@echo
	$(CC) main.o -o oadbg `pkg-config --libs gtk4`

%.o: %.s
	o $<

clean:
	-rm main.o
	-rm main.s.log
	-rm oadbg
	-rm a.out
