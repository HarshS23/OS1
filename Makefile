# Build + run the whole OS: bootloader (0x80000000) + kernel (0x80100000)
#
# make          -> build both
# make run      -> build both, then boot in QEMU
# make clean    -> remove both ELFs

CXX    = riscv64-unknown-elf-g++
CFLAGS = -march=rv64imac_zicsr -mabi=lp64 -ffreestanding -nostdlib \
         -nostartfiles -mcmodel=medany -fno-exceptions -fno-rtti \
         -fno-threadsafe-statics

BOOT_ELF    = bootloader.elf
BOOT_LINKER = src/bootloader/linker/linker.ld
BOOT_SRC    = src/bootloader/bootloader.cpp src/bootloader/uart.cpp \
              src/bootloader/bootloader.S

KERNEL_ELF    = kernal/kernal.elf
KERNEL_LINKER = kernal/linker/linker.ld
KERNEL_SRC    = kernal/kernal_main.cpp kernal/kuart.cpp kernal/kernal_boot.S

# Default target: build both
all: $(BOOT_ELF) $(KERNEL_ELF)

$(BOOT_ELF): $(BOOT_SRC) $(BOOT_LINKER)
	$(CXX) $(CFLAGS) $(BOOT_SRC) -T $(BOOT_LINKER) -o $(BOOT_ELF)

$(KERNEL_ELF): $(KERNEL_SRC) $(KERNEL_LINKER)
	$(CXX) $(CFLAGS) $(KERNEL_SRC) -T $(KERNEL_LINKER) -o $(KERNEL_ELF)

run: all
	qemu-system-riscv64 -machine virt -nographic -bios none \
		-serial mon:stdio \
		-device loader,file=$(KERNEL_ELF),addr=0x80100000 \
		-kernel $(BOOT_ELF)

clean:
	rm -f $(BOOT_ELF) $(KERNEL_ELF)

.PHONY: all run clean