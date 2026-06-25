#include <stdio.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>


#include <kernel/tty.h>
#include <stdbool.h>

void kernel_main(void) {
	// Initlize Terminal 
	terminal_initialize();
	// Initlize Global Discriptor Table
	GDT_INIT();

	// setup idt 
	IDT_INIT();

	// testing if the interrupt works 
	__asm__ volatile ("int $0x3");   
	
	printf("\nHello, kernel World!\n");
}
