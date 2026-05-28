# bootloader writtern in RISC-V 

.section .text # in the linker go to the .text 
.global _start # now start 

_start:
    # displaying interrupts 
    csrw mie, zero # machine interrupt enabled (mie) <- zero 

    # setting the stack pointer 
    la sp, _stack_top

    # now we clear out the bss section 

    la t0, _bss_start  # t0 = _bss_start 
    la t1, _bss_end    # t1 = _bss_end 

bss_loop:
    bge t0, t1, bss_done

    sw zero, 0(t0) 

    addi t0, t0, 4

    j bss_loop

bss_done:
    call main

hang: 
    j hang