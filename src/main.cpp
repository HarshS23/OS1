// this will print to screen and check if the bootloader even worked 
// extern basically tells the compiler don't change this functions name to something else 
// keep it as main 

#include "uart.hpp"

extern "C" void main(){
    uart_putc('H');
}