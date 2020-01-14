# Travis Banken
# 
# Root level makefile for the project

include config.mk
include versions.mk

KERNEL_NAME = pios
TARG_ELF = build/$(KERNEL_NAME)-v$(IMG_VERSION).elf
TARG_IMG = build/$(KERNEL_NAME)-v$(IMG_VERSION).img
LINKER_SCRIPT = build/linker.ld

CC = $(CC_PATH)
LD = $(LD_PATH)

OBJS = $(wildcard */obj/*.o)
INCLUDE = $(patsubst %, -I%/include, $(SUBDIRS))

TESTDIR = test

.PHONY: build
build: $(TARG_ELF)
	@echo "$(TARG_ELF) built, use 'make run' to boot with qemu or copy $(TARG_IMG) to SD card for hardware boot"

.PHONY: $(SUBDIRS)
$(TARG_ELF): $(SUBDIRS)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) $(OBJS) $(INCLUDE) -o $(TARG_ELF)
	$(OBJCOPY) $(TARG_ELF) -O binary $(TARG_IMG)

$(SUBDIRS):
	+$(MAKE) -C $@ -f $@.mk

.PHONY: run
run: build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(TARG_ELF)

.PHONY: tests
tests:
	+$(MAKE) -C $(TESTDIR) run


.PHONY: clean
clean:
	+$(MAKE) -C arch -f arch.mk clean
	+$(MAKE) -C kernel -f kernel.mk clean
	+$(MAKE) -C common -f common.mk clean
	+$(MAKE) -C $(TESTDIR) clean
	rm -f $(TARG_ELF) $(TARG_IMG) coredump*
