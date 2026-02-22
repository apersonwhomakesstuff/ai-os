CC := gcc
LD := ld
AS := nasm

CFLAGS := -m32 -ffreestanding -fno-stack-protector -fno-pic -nostdlib -Wall -Wextra -O2
LDFLAGS := -m elf_i386 -T linker.ld

SRC_C := src/kernel.c
SRC_ASM := src/boot.asm
OBJ := build/kernel.o build/boot.o

KERNEL := build/kernel.bin
ISO := build/ai-os.iso

.PHONY: all clean iso

all: $(KERNEL)

build:
	mkdir -p build

build/kernel.o: src/kernel.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/boot.o: src/boot.asm | build
	$(AS) -f elf32 $< -o $@

$(KERNEL): $(OBJ) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

iso: $(KERNEL)
	./scripts/make_iso.sh $(ISO)

clean:
	rm -rf build isodir/boot/kernel.bin
