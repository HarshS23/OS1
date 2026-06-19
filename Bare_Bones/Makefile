
# Toolchain
AS = i686-elf-as
CC = i686-elf-g++
LD = i686-elf-g++

# Flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -Ikernal
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

# Files
TARGET = myos.bin
ISO = myos.iso
OBJDIR = obj
OBJS = $(OBJDIR)/boot.o $(OBJDIR)/kernel.o $(OBJDIR)/string.o $(OBJDIR)/terminal.o

ISODIR = isodir
GRUBCFG = $(ISODIR)/boot/grub/grub.cfg

# Default target
all: $(TARGET)

# Make sure the obj directory exists before anything compiles into it
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link
$(TARGET): $(OBJS) linker/linker.ld
	$(LD) -T linker/linker.ld -o $@ $(OBJS) $(LDFLAGS)

# Assemble boot.s
$(OBJDIR)/boot.o: boot/boot.s | $(OBJDIR)
	$(AS) boot/boot.s -o $@

# Compile kernel
$(OBJDIR)/kernel.o: kernal/kernal.cc | $(OBJDIR)
	$(CC) $(CFLAGS) -c kernal/kernal.cc -o $@

# Compile string routines
$(OBJDIR)/string.o: kernal/String/string.cc | $(OBJDIR)
	$(CC) $(CFLAGS) -c kernal/String/string.cc -o $@

# Compile terminal routines
$(OBJDIR)/terminal.o: kernal/Terminal/terminal.cc | $(OBJDIR)
	$(CC) $(CFLAGS) -c kernal/Terminal/terminal.cc -o $@

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
	rm -rf $(OBJDIR)
	rm -f $(TARGET) $(ISO)
	rm -rf $(ISODIR)

.PHONY: all iso run run-iso clean