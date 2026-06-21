#include <stdint.h>
#include <kernel/gdt.h>





struct GDT_ENTRY {

    uint16_t limit_low;
    uint16_t base_low; 
    uint8_t base_middle;
    uint8_t access; 
    uint8_t granularity;
    uint8_t base_high;

}__attribute__((packed));

struct GDT_PTR {
    uint16_t limit;
    void* ptr;
}__attribute__((packed));


static struct GDT_ENTRY gdt[5];
static struct GDT_PTR gdtp;
