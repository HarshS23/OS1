#include <stdint.h>
#include <kernel/gdt.h>


// Segment Discriptor 

struct GDT_ENTRY{
    uint16_t Low_Limit;
    uint16_t Low_Base;
    uint8_t Mid_Base;
    uint8_t Access_Byte;
    uint8_t Upper_Limit : 4;
    uint8_t Flags : 4;
    uint8_t Upper_Base;
}__attribute__((packed));


struct GDT_PTR{
    uint16_t GDT_LIMIT; // This is the size of the GDT - 1 (in bytes)
    void* ptr;  // the ptr that points to the entry in GDT
}__attribute__((packed));




// struct GDT_ENTRY {

//     uint16_t limit_low;
//     uint16_t base_low; 
//     uint8_t base_middle;
//     uint8_t access; 
//     uint8_t granularity;
//     uint8_t base_high;

// }__attribute__((packed));

// struct GDT_PTR {
//     uint16_t limit;
//     void* ptr;
// }__attribute__((packed));


// static struct GDT_ENTRY gdt[5];
// static struct GDT_PTR gdtp;