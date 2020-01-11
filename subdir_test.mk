include ../../config.mk

CC = ../../$(CC_PATH)
LD = ../../$(LD_PATH)

INCLUDE = $(patsubst %, -I../../%/include, $(SUBDIRS))
INCLUDE += -I../../test/include


CSRC = $(wildcard *.c)
SSRC = $(wildcard *.s)
COBJS = ${CSRC:.c=.o}
SOBJS = ${SSRC:.s=.o}
# HDRS = $(wildcard include/*.h)
OBJS = $(COBJS) $(SOBJS)

.PHONY: build
build: $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.s $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o
