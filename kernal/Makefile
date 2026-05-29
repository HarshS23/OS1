# Qemu command:  qemu-system-riscv64 -machine virt -nographic -bios none -kernel your-kernel.elf

# target: dependencies
#     command

CXX = riscv64-unknown-elf-g++
TARGET = kernal.elf
LINKER = linker/linker.ld
SRC = kernal_main.cpp kuart.cpp kernal_boot.S 
CFLAGS = -march=rv64imac_zicsr -mabi=lp64 -ffreestanding -nostdlib -nostartfiles -mcmodel=medany -fno-exceptions

$(TARGET): $(SRC)
	$(CXX) $(CFLAGS) $(SRC) -T $(LINKER) -o $(TARGET)

run: $(TARGET)
	qemu-system-riscv64 -machine virt -nographic -bios none -serial mon:stdio -kernel $(TARGET)



clean:
	rm -f $(TARGET)
