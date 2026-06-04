# Qemu command:  qemu-system-riscv64 -machine virt -nographic -bios none -kernel your-kernel.elf

# target: dependencies
#     command

CXX = riscv64-unknown-elf-g++
TARGET = bootloader.elf
LINKER = src/bootloader/linker/linker.ld
SRC = src/bootloader/bootloader.cpp src/bootloader/uart.cpp src/bootloader/bootloader.S
CFLAGS = -march=rv64imac_zicsr -mabi=lp64 -ffreestanding -nostdlib -nostartfiles -mcmodel=medany -fno-exceptions -fno-rtti -fno-threadsafe-statics

$(TARGET): $(SRC)
	$(CXX) $(CFLAGS) $(SRC) -T $(LINKER) -o $(TARGET)

run: $(TARGET)
	qemu-system-riscv64 -machine virt -nographic -bios none -serial mon:stdio -device loader,file=kernal/kernal.elf,addr=0x80100000 -kernel $(TARGET)	

clean:
	rm -f $(TARGET) kernal/kernal.elf
