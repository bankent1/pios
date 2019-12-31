# All vars used in makefiles
# 
# Travis Banken

CC_PATH = gcc-arm-none-eabi-8-2019-q3-update/bin/arm-none-eabi-gcc
AR = ar
LD_PATH = $(CC_PATH)

CFLAGS += -std=gnu99
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -g
DFLAGS += -DDEBUG
# CFLAGS += -O2


# choose raspberry model
ifeq ($(RASPI_MODEL), 2)
	CPU = cortex-a7
	DFLAGS += -DMODEL_2
else ifeq ($(RASPI_MODEL), 3)
	CPU = cortex-a53
	DFLAGS += -DMODEL_3
else ifeq ($(RASPI_MODEL), 1)
	CPU = arm1176jzf-s
	DFLAGS += -DMODEL_1
else
	# default raspi 2
	CPU = cortex-a7
	DFLAGS += -DMODEL_2
endif

VIRTUALIZED = 1
# check if virtual
ifeq ($(VIRTUALIZED), 1)
	DFLAGS += -DVIRTUALIZED
endif

# TODO: option for 64 support
ARCH = 32AArch
DFLAGS += -DAARCH_32

LDFLAGS = -mcpu=$(CPU) -ffreestanding -nostdlib
# LDFLAGS += -O2

CFLAGS += -mcpu=$(CPU) -fpic -ffreestanding

CFLAGS += $(DFLAGS)

SUBDIRS = arch kernel common
