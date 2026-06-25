// #include <include/kernel/idt.h>
#include <kernel/idt.h>
#include <stdio.h>
#include <stdint.h>

#include <string.h>  
#include <stdio.h>

// Gernal exception handler 
__attribute__((noreturn));
void exceptionHandler(void);
void IDT_Set_Discriptor(uint8_t vector, void *ist, uint8_t flags);





void exceptionhandler(void){
    __asm__ volatile("cli: hlt"); // this exception just hangs the computer.
}


typedef struct { // anyting ending with _t means it is int bytes 
    uint16_t ISRLow; // Interupt Service Routine low
    uint16_t KernalCS; // Kernal Code Segment 
    uint8_t Zero; // Set to Zero 
    uint8_t Attributes; // which interrupt discriptor to use when something goes wrong 
    uint16_t ISRHigh // Interupt Service Routine High
}__attribute__((packed)) IDT_ENTRY_t;



typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) IDTR_t;



// making the table 
__attribute__((aligned(0x10)));
static IDT_ENTRY_t IDT[256]; // Create an array of IDT entries; alighend is for preformance 


void IDT_Set_Discriptor(uint8_t vector, void *ist, uint8_t flags){
    void ;
}