
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
ifndef compilerflags
compilerflags=${linkerflags}
endif

OFLAGS=x_file 2 include_sec 1

proj=oadbg

all: ${proj}

${proj}: main.o
	${OLINK} main.oc.log
	@echo
	$(CC) ${linkerflags} $< -o ${proj} -lorb `pkg-config --libs ruby-3.5`
	# `pkg-config --libs gtk4`

%.o: %.oc
	${OCOMP} $< ${OFLAGS}
	${OCONV} $<.x
	$(CC) ${compilerflags} -c -w $*.c

clean:
	-rm -f main.o
	-rm -f main.oc.log
	-rm -f main.oc.x
	-rm -f main.c
	-rm -f ${proj}

.PHONY: all clean
