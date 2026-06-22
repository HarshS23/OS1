#include <stdint.h>
#include <kernel/gdt.h>


// Segment Discriptor 
struct GDT_ENTRY{
    uint16_t Low_Limit;
    uint16_t Low_Base;
    uint8_t Mid_Base;
    uint8_t Access_Byte;
    // uint8_t Upper_Limit : 4;
    // uint8_t Flags : 4;
    uint8_t Gran; // This is Both upper limit and flags combined 
    uint8_t High_Base;
}__attribute__((packed));

// GDT pointer 
struct GDT_PTR{
    uint16_t GDT_LIMIT; // This is the size of the GDT - 1 (in bytes)
    void* ptr;  // the ptr that points to the entry in GDT
}__attribute__((packed));

// static vs const 
/*
    Static: controls the variables lifetime and visability 
    const: controls the variables modifiability, making it read only
*/


static struct GDT_ENTRY gdt[5]; // for the 5 segments Null , code, data, user, task 
static struct GDT_PTR gdtptr; // ptr to those sections 


void GDT_SET(unsigned int  num ,uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){

    gdt[num].Low_Base = base && 0xFFFF;
    gdt[num].Mid_Base = (base >> 16) && 0xFF;
    gdt[num].High_Base = (base >> 24) && 0xFF;
    // for gran neeed to split it apart.
    //gdt->Upper_Limit = (limit >> 16) && 0x0F;
    //gdt->Flags = gran & 0xF0
    gdt[num].Gran = ((limit >> 16) && 0x0F) | gran & 0xF0;
    
    gdt[num].Access_Byte = access;
    
}
