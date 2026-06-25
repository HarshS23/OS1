.global idt_load 
.section .text 

idt_load:
    push %ebp
    mov %esp ,%ebp
    push %eax 
    movl 8(%ebp), %eax # point to the idtr Struct 
    pushfl
    cli 
    lidt (%eax)
    popfl 
    pop (%eax)
    leave 
    ret

