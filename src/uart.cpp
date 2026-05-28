// UART = Universal Asynchronous Receiver Transmitter
// functions 
#include "uart.hpp"

void uart_putc(char c){
    volatile char* uart = (volatile char*)0x09000000;
    *uart = c;
}