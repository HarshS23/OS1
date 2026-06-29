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
    "Coprocessor Segment Overrun",
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

static void print_hex(uint32_t v) {
    char buf[9];
    const char *d = "0123456789ABCDEF";
    for (int i = 7; i >= 0; i--) { buf[i] = d[v & 0xF]; v >>= 4; }
    buf[8] = '\0';
    printf("0x%s", buf);
}




void Exception_Handler(int_frame_t *intFrame){

    uint32_t Vector = intFrame->VectorNum;
    printf("-------------------------------------\n");
    printf("              CPU EXCEPTION:           ");
    printf("\n");
    printf("%s", (Vector < 32) ? ExceptionType[Vector] : "Unknown");
    printf("\n  vector     = "); print_hex(Vector);
    printf("\n  error code = "); print_hex(intFrame->ErrorCode);
    printf("\n  eip        = "); print_hex(intFrame->eip);
    printf("\n  cs         = "); print_hex(intFrame->cs);
    printf("\n  eflags     = "); print_hex(intFrame->eflags);

    if(Vector == 14){ // page fault
        uint32_t faultAddr;
        __asm__ volatile("mov %%cr2, %0" : "=r"(faultAddr));
        printf("\n  cr2 (fault addr) = "); print_hex(faultAddr);
    }

    printf("\n-------------------------------------\n");
    __asm__ volatile("cli");
    for (;;) __asm__ volatile("hlt");



}