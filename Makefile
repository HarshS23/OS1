# Qemu command:  qemu-system-riscv64 -machine virt -nographic -bios none -kernel your-kernel.elf

# target: dependencies
#     command

CXX = riscv64-unknown-elf-g++
TARGET = bootloader.elf
LINKER = linker/linker.ld
SRC = src/bootloader.cpp src/uart.cpp src/bootloader.S
CFLAGS = -march=rv64imac_zicsr -mabi=lp64 -ffreestanding -nostdlib -nostartfiles -mcmodel=medany

$(TARGET): $(SRC)
	$(CXX) $(CFLAGS) $(SRC) -T $(LINKER) -o $(TARGET)

run: $(TARGET)
	qemu-system-riscv64 -machine virt -nographic -bios none -serial mon:stdio -kernel $(TARGET)

clean:
	rm -f $(TARGET)
