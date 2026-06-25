# .extern General_Handler

.extern general_handler
.global isr_vectors

.macro with_error_code num
isr_\num:
    pushl $\num                 # push interrupt number (CPU already pushed error code)
    jmp int_wrapper
.endm

.macro without_error_code num
isr_\num:
    pushl $0                    # simulate error code for int_frame_t
    pushl $\num
    jmp int_wrapper
.endm

.macro ax_to_seg_regs
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
.endm

.section .text
int_wrapper:
    cli
    movl %esp, frame_ptr        # save esp -> points at int_num/err_code/eip/...
    pushal                      # save general-purpose registers

    movw %ds, %ax
    pushl %eax                  # save segment value
    movw $0x10, %ax             # switch to kernel data segment
    ax_to_seg_regs

    movl %esp, %eax
    pushl %eax                  # arg2: &int_regs_t
    movl frame_ptr, %eax
    pushl %eax                  # arg1: &int_frame_t
    call general_handler
    addl $0x8, %esp             # remove the two arguments

    popl %eax                   # restore segment value
    ax_to_seg_regs
    popal

    addl $0x8, %esp             # remove interrupt number + error code
    sti
    iret

# Exception vectors
without_error_code  0
without_error_code  1
without_error_code  2
without_error_code  3
without_error_code  4
without_error_code  5
without_error_code  6
without_error_code  7
with_error_code     8
without_error_code  9
with_error_code     10
with_error_code     11
with_error_code     12
with_error_code     13
with_error_code     14
without_error_code  15
without_error_code  16
with_error_code     17
without_error_code  18
without_error_code  19
without_error_code  20
without_error_code  21
without_error_code  22
without_error_code  23
without_error_code  24
without_error_code  25
without_error_code  26
without_error_code  27
without_error_code  28
without_error_code  29
with_error_code     30
without_error_code  31
# IRQs
without_error_code  32
without_error_code  33
without_error_code  34
without_error_code  35
without_error_code  36
without_error_code  37
without_error_code  38
without_error_code  39
without_error_code  40
without_error_code  41
without_error_code  42
without_error_code  43
without_error_code  44
without_error_code  45
without_error_code  46
without_error_code  47
# Syscall trigger
without_error_code  48

.section .bss
.align 4
frame_ptr:
    .skip 4

.section .data
isr_vectors:
.irp num, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48
    .long isr_\num
.endr
