// UART = Universal Asynchronous Receiver Transmitter
// functions 
#include "kuart.hpp"

void uart_putc(char c){
    volatile char* uart = (volatile char*)0x10000000;
    volatile char* lsr = (volatile char*)(0x10000000 + 5);

    while(!(*lsr & (1 << 5)));

    *uart = c;
}

void uart_puts(const char* s){
    volatile char* uart = (volatile char*)0x10000000;
    
    while(*s != '\0'){
        uart_putc(*s);
        s++;
    }

}