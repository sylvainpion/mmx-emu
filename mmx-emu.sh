#!/bin/sh
#
# Simple script to lunch your program with the MMX emulator.
#

# Where's the library ?
#
# LIB_MMX_EMU_PATH=/usr/local/lib
LIB_MMX_EMU_PATH=.

# If you want to suppress support for a specific instruction set,
# uncomment the corresponding line.
#
# export MMX_EMU_NO_LOOK_AHEAD
# export MMX_EMU_NO_CYRIX_EMMX
# export MMX_EMU_NO_AMD_3DNOW


# We lunch the thing.
LD_PRELOAD=$LIB_MMX_EMU_PATH/libmmxemu.so
export LD_PRELOAD
exec $@
