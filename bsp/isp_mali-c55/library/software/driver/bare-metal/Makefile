#----------------------------------------------------------------------------------
# SPDX-License-Identifier: BSD-3-Clause
#
# Copyright (c) 2016-2022, Arm Limited. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# - Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice, this
#    list of conditions and the following disclaimer in the documentation and/or
#    other materials provided with the distribution.
# - Neither the name of ARM nor the names of its contributors may be used to
#    endorse or promote products derived from this software without specific prior
#    written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#----------------------------------------------------------------------------------


LINK_TARGET = mali_iv021_isp_fw.elf

ifeq ($(CROSS_COMPILE),)
    $(error "Please export CROSS_COMPILE variable before build")
else
    _CROSS_COMPILE=${CROSS_COMPILE}
endif

CC=$(_CROSS_COMPILE)gcc

CFLAGS=-I src -I app/ -I app/control -I src/fw -I src/fw_lib -I src/driver/sensor -I src/driver/lens -I inc -I inc/isp -I inc/api -I inc/sys -c
CFLAGS+=-march=armv8.1-m.main -mfloat-abi=soft -Os -Wno-unused-function
ODIR=obj
SOURCES = $(wildcard app/*.c app/control/*.c src/*.c src/fw/*.c src/fw_lib/*.c src/platform/*.c  src/driver/*/*.c src/calibration/*.c )
TOBJ = $(notdir $(SOURCES:.c=.o))
OBJ = $(addprefix $(ODIR)/, $(TOBJ) )
LDFLAGS=-march=armv8.1-m.main -mfloat-abi=soft -specs=nosys.specs

ifneq ($(wildcard src/fw_lib/libacamera_isp.a),)
LDFLAGS+=-Lsrc/fw_lib -lacamera_isp
endif

ifneq ($(wildcard src/fw_lib/libacamera_alg_core-gcc-armv8.1-m.main-float-abi-soft.a),)
LDFLAGS+=-Lsrc/fw_lib -lacamera_alg_core-gcc-armv8.1-m.main-float-abi-soft
endif

REBUILDABLES = $(OBJ) $(LINK_TARGET)

.PHONY: all
all : $(LINK_TARGET)
	echo All done

$(shell  mkdir -p $(ODIR))

$(LINK_TARGET) : $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(ODIR)/%.o: app/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: app/control/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/calibration/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/driver/sensor/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/driver/lens/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/platform/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/fw/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: src/fw_lib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(REBUILDABLES)
	echo Clean done
