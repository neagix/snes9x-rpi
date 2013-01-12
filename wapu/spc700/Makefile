# Makefile for MS Visual C

ALL : spc700a.s

spc700a.s:	spcgen
	./spcgen.x

spcgen:
	g++ spcgen.c -o spcgen.x -pedantic

clean:
	rm -f spc700a.s
	rm -f spcgen.x
