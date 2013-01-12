# Makefile for MS Visual C

all : spc700a.s

spc700a.s:	spcgen
	./spcgen.x

spcgen:
	g++ spcgen.c -o spcgen.x -pedantic

clean:
	rm -f spc700a.s
	rm -f spcgen.x
