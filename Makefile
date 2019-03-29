CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

PAL_FILES = $(wildcard data/*.pal)
BIN_FILES = $(wildcard data/*.bin)
SRC_FILES = $(wildcard src/*.c)

all: main.gba

utildir:
	make -C util/

datadir:
	make -C data/

srcdir:
	make -C src/

main.gba: utildir datadir srcdir $(PAL_FILES) $(BIN_FILES) $(SRC_FILES)
	$(CC) -Tlink.txt data/*.o src/*.o -o main.bin -fwhole-program
	$(OBJCOPY) -O binary -j .text main.bin main.gba
	gbafix main.gba


clean:
	rm main.bin main.gba src/*.o data/*.h data/*.o data/*.c