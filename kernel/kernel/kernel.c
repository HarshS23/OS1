#include <stdio.h>
#include <kernel/gdt.h>


#include <kernel/tty.h>
#include <stdbool.h>

void kernel_main(void) {
	terminal_initialize();

	if (GDT_INIT()) {
		printf("\nGDT initialized\n");
	} else {
		printf("\nGDT initialization failed\n");
	}


	printf("Hello, kernel World!\n");
}
