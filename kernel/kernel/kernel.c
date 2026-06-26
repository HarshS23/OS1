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
	//__asm__ volatile ("int $0x3");   
	printf("####################################################\n");
	printf("                 Hello, kernel World!               \n");
	printf("####################################################\n");

	printf("\nThis is my Operating System Project. I made this to gain a better understanding"
		    " of how a computer works more specifically an Operating System.\n"
		    "I've currently finished the Global Discriptor Table, and a basic Interrupt \n Descriptor Table."
			" My future plans are to work on\n"
			"\n1. Exceptions \n" 
			"2. IRQ \n" 
			"3. System Calls \n"
			"4. Paging (Basic Demand Paging),\n"
			"5. Memeory Management \n");
	
	printf("####################################################\n");
	



	__asm__ volatile ("int $0x3");   

}
