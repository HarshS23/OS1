#include <stdio.h>
#include <kernel/gdt.h>


#include <kernel/tty.h>
#include <stdbool.h>

void kernel_main(void) {
	// Initlize Terminal 
	terminal_initialize();
	// Initlize Global Discriptor Table
	GDT_INIT();
	printf("\nHello, kernel World!\n");
}
