# Travis Banken
# 
# Root level makefile for the project

include config.mk

VERSION = 0.1
IMG_NAME = build/pios-v$(VERSION).img
LINKER_SCRIPT = build/linker.ld

CC = $(CC_PATH)
LD = $(LD_PATH)

OBJS = $(wildcard */obj/*.o)
INCLUDE = $(patsubst %, -I%/include, $(SUBDIRS))

.PHONY: build
build: $(IMG_NAME)
	@echo "$(IMG_NAME) built, use 'make run' to boot img with qemu"

.PHONY: $(SUBDIRS)
$(IMG_NAME): $(SUBDIRS)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) $(OBJS) $(INCLUDE) -o $(IMG_NAME)

$(SUBDIRS):
	+$(MAKE) -C $@ -f $@.mk

.PHONY: run
run: build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME)

.PHONY: clean
clean:
	+$(MAKE) -C arch -f arch.mk clean
	+$(MAKE) -C kernel -f kernel.mk clean
	+$(MAKE) -C common -f common.mk clean
	rm -f $(IMG_NAME)
