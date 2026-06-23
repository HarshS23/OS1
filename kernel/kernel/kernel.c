#include <stdio.h>
#include <kernel/gdt.h>


#include <kernel/tty.h>
#include <stdbool.h>

void kernel_main(void) {
	terminal_initialize();
	GDT_INIT();
	printf("Hello, kernel World!\n");
}
