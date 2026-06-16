/* 

Kernal Entry Point, that sets up the enviroment 
   Using GNU assmbler 



*/

/*  Declare Constants for multi boot header */ 
.set ALIGN, 1<<0    /* aligning loaded modules on page boundaries */
.set MEMINFO, 1<<1   /* Provide a Memeory Map */
.set FLAGS, ALIGN | MEMINFO /* MutliBoot Flag Field*/
.set MAGIC, 0x1BADB002 /* Magic number that helps you find the headers (Kernal scans for this value )*/
.set CHECKSUM, -(MAGIC + FLAGS ) /* Check sum above to prove we are in Multi boot*/

/*
Declaring a mutli boot header that marks the program as a kernal. These are magic values that are documented in the 
magic boot standard  
*/ 

.section .multiboot 
.align 4 
.long MAGIC 
.long FLAGS 
.long CHECKSUM

/* 
    Multiboot standard does not define the stack pointer registers, its up to the kernal to provide the stack 
    then allocate 16384, and creating a symbol at the top the stack grows downwards in x86. 
*/

.section .bss 
.align 16 
stack_bottom:
    .skip 16384
stack_top:
    /* 
        Linker script has a _start section as the entry point to the kernal 
        Bootloader will jump to this once the kernal is loaded 
    */
    
.section .text 
.global _start 
.type _start , @function 

_start: 
    /* The booloader loads us into a 32 bit protected mode on x86 
       everything is disable, interupts, paging, The kernal has full cpu control 
       no printing no nothing, I have to create everyting from scratch. meaning making use of 
       all hardware features. 
    */

    /* 
    Setting up the stack, we set the esp register to the point to the top of the stack 
    */

    mov $stack_top, %esp

    call kernal_main /*  This enters the high level kernal */

    /*
	If the system has nothing more to do, put the computer into an
	infinite loop. To do that:
	1) Disable interrupts with cli (clear interrupt enable in eflags).
	   They are already disabled by the bootloader, so this is not needed.
	   Mind that you might later enable interrupts and return from
	   kernel_main (which is sort of nonsensical to do).
	2) Wait for the next interrupt to arrive with hlt (halt instruction).
	   Since they are disabled, this will lock up the computer.
	3) Jump to the hlt instruction if it ever wakes up due to a
	   non-maskable interrupt occurring or due to system management mode.
	*/

    cli
1:  hlt 
    jmp 1b 

.size _start, . - _start 





