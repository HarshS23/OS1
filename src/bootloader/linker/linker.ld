/*
       0x80000000 -- start of ram / start the bootloader at this address
        text 
        data 
        bss 
        0x80100000; -- move kernal to this address 
*/

ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text.boot)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }
    
    .data : {
        *(.data)
    }

    .bss : {
        _bss_start = .;
        *(.bss)
        _bss_end = .; 
    }

    . = ALIGN(16);
    . = . + 0x4000;
    _stack_top = .;
}