CC = arm-none-eabi-gcc
AS = arm-none-eabi-as

OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -ffreestanding -flto

ASRC = $(wildcard *.s)
AOBJ = $(ASRC:.s=.o)

CSRC = $(wildcard *.c)
COBJ = $(CSRC:.c=.o)

all: $(COBJ) $(AOBJ)

$(AOBJ): %.o: %.s
	$(AS) $^ -c -o $@

$(COBJ): %.o: %.c
	$(CC) $(CFLAGS) -I../include $^ -c -o $@

