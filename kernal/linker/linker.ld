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
    . = 0x80100000;

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
        *(COMMON)
        *(.bss)
        _bss_end = .; 
    }

    . = . + 0x1000;
    _stack_top = .;
}