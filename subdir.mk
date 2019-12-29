include ../config.mk

CC = ../$(CC_PATH)
LD = ../$(LD_PATH)

INCLUDE = $(patsubst %, -I../%/include, $(SUBDIRS))

OBJDIR = obj

CSRC = $(wildcard *.c)
SSRC = $(wildcard *.s)
COBJS = ${CSRC:.c=.o}
COBJS := $(OBJDIR)/$(COBJS)
SOBJS = ${SSRC:.s=.o}
SOBJS := $(OBJDIR)/$(SOBJS)
HDRS = $(wildcard include/*.h)
OBJS = $(COBJS) $(SOBJS)

.PHONY: build
build: $(OBJS)
	@echo "finished building $(OBJS)"

$(COBJS): $(CSRC) $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(SOBJS): $(SSRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*
