CC = arm-none-eabi-gcc

BMP = $(wildcard *.bmp)
PAL = $(wildcard *.pal)
CSRC = $(BINS:.bin=.c)
OUT  = $(BINS:.bin=.o)

BINS = $(wildcard *.bin) $(PAL:.pal=.bin) $(BMP:.bmp=.bin)

all: $(OUT)
	cat *.h > ../include/data.h

%.bin: %.bmp
	../util/bmp_to_bin $^

%.bin: %.pal
	../util/pal_to_bin $^

%.c : %.bin
	raw2c $^

%.o: %.c
	$(CC) $^ -ffreestanding -c