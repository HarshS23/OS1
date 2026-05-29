// this will print to screen and check if the bootloader even worked 
// extern basically tells the compiler don't change this functions name to something else 
// keep it as main 

#include "uart.hpp"

extern "C" void bootloader_main(){
    uart_putc('\n');
    uart_puts("BOOTING SEQUENCE INITIATED\n");

    // The bootloader places the kernal code at 0x80100000
    // so the kernal can run
    void(*jump)() = (void (*)())0x80100000;
    jump();
    
}