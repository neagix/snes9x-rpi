== snes9x-rpi

This is a fork of https://github.com/neagix/snes9x-rpi.git with following changes:

- support of OpenGL ES direct rendering (added by neagix)
- adaptions to run on Raspberry PI (added by neagix)

The status is *NOT WORKING*

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
