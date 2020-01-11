# Travis Banken
# 
# Test Makefile
# 
# Root level makefile for testing the project

include ../config.mk
include ../versions.mk

TARGET = test_pios-v$(IMG_VERSION).elf
LINKER_SCRIPT = ../build/linker.ld

CC = ../$(CC_PATH)
LD = ../$(LD_PATH)

OBJS = $(wildcard ../*/obj/*.o)
OBJS += $(wildcard ../*/test/*.o)
FILTERED_OBJS = $(filter-out ../arch/obj/boot.o, $(OBJS))
INCLUDE = $(patsubst %, -I../%/include, $(SUBDIRS))
INCLUDE += -Iinclude/

TEST_CSRC = $(wildcard *.c)
TEST_COBJ = ${TEST_CSRC:.c=.o}
TEST_SSRC = $(wildcard *.s)
TEST_SOBJ = ${TEST_SSRC:.s=.o}

TEST_SUBDIRS = $(patsubst %, %/test, $(SUBDIRS))

.PHONY: build
build: $(TARGET)
	@echo "$(TARGET) built, use 'make run' to boot with qemu"

.PHONY: $(SUBDIRS) $(TEST_SUBDIRS) 
$(TARGET): $(TEST_SUBDIRS) $(SUBDIRS) $(TEST_COBJ) $(TEST_SOBJ)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) $(FILTERED_OBJS) $(TEST_COBJ) $(TEST_SOBJ) $(INCLUDE) -o $(TARGET)


$(SUBDIRS):
	+$(MAKE) -C ../$@ -f $@.mk
	+$(MAKE) -C ../$@/test -f $@_test.mk

%.o: %.s
	@echo "DOING IT"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: run
run: build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(TARGET)

.PHONY: clean
clean:
	+$(MAKE) -C ../arch -f arch.mk clean
	+$(MAKE) -C ../arch/test -f arch_test.mk clean
	+$(MAKE) -C ../kernel -f kernel.mk clean
	+$(MAKE) -C ../kernel/test -f kernel_test.mk clean
	+$(MAKE) -C ../common/ -f common.mk clean
	+$(MAKE) -C ../common/test -f common_test.mk clean
	rm -f $(TARGET) *.o
