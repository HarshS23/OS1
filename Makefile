# Toolchain
AS = i686-elf-as
CC = i686-elf-g++
LD = i686-elf-gcc

# Flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

# Files
TARGET = myos.bin
ISO = myos.iso
OBJS = boot.o kernel.o

ISODIR = isodir
GRUBCFG = $(ISODIR)/boot/grub/grub.cfg

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS) linker.ld
	$(LD) -T linker.ld -o $@ $(OBJS) $(LDFLAGS)

# Assemble boot.s
boot.o: boot.s
	$(AS) boot.s -o boot.o

# Compile kernel
kernel.o: kernal.cc
	$(CC) $(CFLAGS) -c kernal.cc -o kernel.o

# Build ISO
iso: $(TARGET)
	mkdir -p $(ISODIR)/boot/grub
	cp $(TARGET) $(ISODIR)/boot/$(TARGET)
	echo 'menuentry "myos" { multiboot /boot/$(TARGET) }' > $(GRUBCFG)
	grub-mkrescue -o $(ISO) $(ISODIR)

# Run in QEMU (no ISO needed)
run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

# Run with ISO
run-iso: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) $(ISO)
	rm -rf $(ISODIR)

.PHONY: all iso run run-iso clean