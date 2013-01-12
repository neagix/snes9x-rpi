
all: ogl

#ogl:
#   ./remotemake

Makefile: configure Makefile.in
	@echo "Makefile is older than configure or in-file. Run configure or touch Makefile."
	exit 1

Makefile.in:
	make -C ogl Makefile.in

configure: ogl/configure.ac
	@echo "configure is older than in-file. Run autoconf or touch configure."
	exit 1

clean:
	make -C ogl clean
