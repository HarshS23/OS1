/*
        0x80000000 -- start of ram 
        text 
        data 
        bss 
*/

ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text.boot)
        *(.text)
    }
    
    .data : {
        *(.data)
    }

    .bss : {
        _bss_start = .;
        *(.bss)
        _bss_end = .; 
    }

    . = . + 0x1000;
    _stack_top = .;
}