#include <kernel/isr.h>




char *ExceptionType[] = {
    "Division Error",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode", 
    "Device Not Avaliable",
    "Double Fault",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault", // triple fault
    "Page Fault",
    "Intel Resevered", 
    "FPU Floating Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point Exception",
    "Virtualization Exception",
    "Control Exception Fault",
    "Intel Resevered", 
    "Intel Resevered", 
    "Intel Resevered", 
    "Intel Resevered", 
    "Intel Resevered", 
    "Hypervisor injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Intel Resevered", 
    "Triple Fault",
    "Intel Resevered"
};


static void Exception_Handler(int_frame_t *intFrame){
    void; // need to implement exception for paging
}