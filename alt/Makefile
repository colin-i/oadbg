
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
linkerflags=-O3 -s
endif

OFLAGS=x_file 2

proj=actionswf-alt

all: ${proj}

${proj}: main.o
	${OLINK} main.s.log
	@echo
	$(CC) ${linkerflags} $< -o ${proj}

%.o: %.s
	${OCOMP} $< ${OFLAGS}
	${OCONV} $<.x
	$(CC) -c $*.c

clean:
	-rm -f main.o
	-rm -f main.s.log
	-rm -f main.s.x
	-rm -f main.c
	-rm -f ${proj}
