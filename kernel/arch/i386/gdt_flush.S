.global gdt_flush
.type gdt_flush, @function 

gdt_flush: 
    movl 4 (%esp), %eax  # get the pointer to the gdt_ptr struct 
    lgdt  (%eax) # load the gdt 
    
    movw $0x10, %ax       # 0x10 = kernel data selector
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

    ljmp $0x08, $.flush2  # far jump reloads CS with kernel code selector (0x08)
.flush2:
	ret
.size gdt_flush, . - gdt_flush
