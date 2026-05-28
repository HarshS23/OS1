#pragma once 

// UART = Universal Asynchronous Receiver Transmitter
// functions 
void uart_putc(char c);

void uart_putc(char c){
    volatile char* uart = (volatile char*)0x09000000;
}