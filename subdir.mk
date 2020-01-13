include ../versions.mk
include ../config.mk

CC = ../$(CC_PATH)
LD = ../$(LD_PATH)

INCLUDE = $(patsubst %, -I../%/include, $(SUBDIRS))

OBJDIR = obj

CSRC = $(wildcard *.c)
SSRC = $(wildcard *.s)
COBJS = ${CSRC:.c=.o}
COBJS := $(patsubst %, $(OBJDIR)/%, $(COBJS))
SOBJS = ${SSRC:.s=.o}
SOBJS := $(patsubst %, $(OBJDIR)/%, $(SOBJS))
HDRS = $(wildcard include/*.h)
OBJS = $(COBJS) $(SOBJS)

.PHONY: build
build: $(OBJS)

$(OBJDIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: %.s $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*
