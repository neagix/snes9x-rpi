== snes9x-rpi

This is a fork of current (as of December 2012) snes9x git repository,
with the following changes:

- support of OpenGL ES direct rendering (added by neagix)
- SDL input and audio code from snes9x-sdl (merged from https://github.com/domaemon/snes9x-sdl)
- SPC700 ARM-optimized core from a snes9x-0.40 fork (by notaz)

NOTE: the directory os9x-cpu is the original ARM-optimized opens9x core by notaz, but is not being used

The status is *NOT WORKING*, video works but audio is a no-no.

Feel free to pick it up and find what's going wrong there...

== How to compile

The configure script seems to be broken

git clone https://github.com/neagix/librpi2d && \
make -C librpi2d && \
make -C wapu/spc700 && \
make

== How to cross-compile

Assuming you have distcc correctly configured:

export PATH=/usr/lib/distcc:${PATH}
#export DISTCC_VERBOSE=1
#export DISTCC_FALLBACK=0
export ARCH=arm
make
