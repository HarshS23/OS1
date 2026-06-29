#ifndef _ISR_H_
#define _ISR_H_

#include <stdint.h>
#include <stdio.h>

#define ENABLE_INTERRUPTS \
    __asm__ __volatile__("sti":::)

#define PAUSE_CPU \
    __asm__ __volatile__("hlt":::)


typedef struct {
    uint32_t VectorNum;
    uint32_t ErrorCode;
    uint32_t eip; // Instruction Pointer 
    uint32_t cs; // code segment 
    uint32_t eflags; // flages register
    uint32_t esp; // stack pointer 
    uint32_t ss; // stack segment 

}int_frame_t; // frame in bytes



extern char *ExceptionType[];
void Exception_Handler(int_frame_t *frame);

#endif