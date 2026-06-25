// #include <include/kernel/idt.h>
#include <kernel/idt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>  
#include <stdio.h>

#define GDT_OFFSET_KERNEL_CODE 0x08
#define IDT_MAX_DESCRIPTORS 256


// Gernal exception handler 
__attribute__((noreturn));
void general_handler(void);
void IDT_Set_Discriptor(uint8_t vector, void *ist, uint8_t flags);





void general_handler(void){
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
static IDT_ENTRY_t IDT[IDT_MAX_DESCRIPTORS]; // Create an array of IDT entries; alighend is for preformance 

// extern void *isr_vectors[]; //from isr.asm
// extern void idt_load(uint32_t);



void IDT_Set_Discriptor(uint8_t vector, void *isr, uint8_t flags){
    IDT_ENTRY_t* discriptor  = &IDT[vector];

    discriptor->ISRLow = (uint32_t) isr & 0xFFFF;
    discriptor->KernalCS = GDT_OFFSET_KERNEL_CODE;
    discriptor->Attributes = flags;
    discriptor->ISRHigh = (uint32_t) isr >> 16;
    discriptor->Zero = 0;
   
}

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];


void IDT_INIT(void){
    IDTR_t idtr;
    idtr.base = (uintptr_t) &IDT[0];
    idtr.limit = (uint16_t) sizeof(IDT_ENTRY_t) * IDT_MAX_DESCRIPTORS - 1;

    // basically set the idt descriptor with the proper interrupt
    for(uint8_t vector = 0; vector < 32; vector++){
        IDT_Set_Discriptor(vector,isr_stub_table[vector], 0x8E); // setting the descriptor
        vectors[vector] = true; // mark as taken after setting the descriptor
    }

    __asm__ volatile ("lidt %0," : : "m" (idtr)); // load the new idt
    __asm__ volatile ("sti"); // set the interrupt flags 


    
    
}