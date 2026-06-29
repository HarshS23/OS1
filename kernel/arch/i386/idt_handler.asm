extern general_handler
global idt_load
global isr_stub_table

%macro isr_err_stub 1
isr_stub_%+%1:
    push %1
    jmp isr_common
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push 0
    push %1
    jmp isr_common
%endmacro

section .text
idt_load:
    mov eax, [esp+4]
    lidt [eax]
    ret

isr_common:
    pushad                  ; EAX ECX EDX EBX ESP EBP ESI EDI = 32 bytes
    mov ax, ds
    push eax                ; save data segment (4 bytes)

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    add eax, 36             ; skip ds(4) + pushad(32) -> points at VectorNum
    push eax                ; arg: int_frame_t *frame
    call general_handler
    add esp, 4              ; pop the argument

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popad
    add esp, 8             ; drop vector + error code
    iret


; isr_common:
;     pushad
;     mov ax, ds
;     push eax
;     mov ax, 0x10
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     call general_handler
;     pop eax
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     popad
;     add esp, 8          ; drop pushed int number + error code
;     iret

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_err_stub    21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_no_err_stub 30
isr_no_err_stub 31

section .data
isr_stub_table:
%assign i 0
%rep 32
    dd isr_stub_%+i
    %assign i i+1
%endrep








; -----------------------------------------------------------------------------------
;                               OSDEV ASSEMBLY CODE
; -----------------------------------------------------------------------------------
; extern ExceptionHandler

; %macro isr_err_stub 1
; isr_stub_%+%1:
;     call exception_handler
;     iret 
; %endmacro
; ; if writing for 64-bit, use iretq instead
; %macro isr_no_err_stub 1
; isr_stub_%+%1:
;     call exception_handler
;     iret
; %endmacro


; extern exception_handler
; isr_no_err_stub 0
; isr_no_err_stub 1
; isr_no_err_stub 2
; isr_no_err_stub 3
; isr_no_err_stub 4
; isr_no_err_stub 5
; isr_no_err_stub 6
; isr_no_err_stub 7
; isr_err_stub    8
; isr_no_err_stub 9
; isr_err_stub    10
; isr_err_stub    11
; isr_err_stub    12
; isr_err_stub    13
; isr_err_stub    14
; isr_no_err_stub 15
; isr_no_err_stub 16
; isr_err_stub    17
; isr_no_err_stub 18
; isr_no_err_stub 19
; isr_no_err_stub 20
; isr_no_err_stub 21
; isr_no_err_stub 22
; isr_no_err_stub 23
; isr_no_err_stub 24
; isr_no_err_stub 25
; isr_no_err_stub 26
; isr_no_err_stub 27
; isr_no_err_stub 28
; isr_no_err_stub 29
; isr_err_stub    30
; isr_no_err_stub 31


; global isr_stub_table
; isr_stub_table:
; %assign i 0 
; %rep    32 
;     dd isr_stub_%+i ; use DQ instead if targeting 64-bit
; %assign i i+1 
; %endrep







; -----------------------------------------------------------------------------------
;                                    OLD CODE 
; -----------------------------------------------------------------------------------
; extern general_handler
; global isr_vectors

; %macro with_error_code 1
; isr_%+%1:
; 	push %1	; Push interrupt number
; 	jmp int_wrapper
; %endmacro

; %macro without_error_code 1
; isr_%+%1:
; 	push 0	; Simulate error code for int_frame_t 
; 	push %1
; 	jmp int_wrapper
; %endmacro

; %macro ax_to_seg_regs 0
; 	mov ds, ax
; 	mov es, ax
; 	mov fs, ax
; 	mov gs, ax
; %endmacro

; section .text
; int_wrapper:
; 	cli

; 	mov [frame_ptr], esp
; 	pushad	; Save gp registers
	
; 	mov ax, ds
; 	push eax ; Save seg registes value

; 	; Ensure that we operate in kernel segments
; 	mov ax, 0x10
; 	ax_to_seg_regs

; 	; Push arguments and call handler

; 	mov eax, esp
; 	push eax ; &int_regs_t

; 	mov eax, [frame_ptr]
; 	push eax ; &int_frame_t
; 	call general_handler

; 	; Remove arguments from stack
; 	add esp, 0x8

; 	; Restore state of interrupted program
; 	pop eax
; 	ax_to_seg_regs
; 	popad

; 	; Remove exception number and error code
; 	add esp, 0x8

; 	; Enable interrupts and return
; 	sti
; 	iret

; ; Define exceptions labels
; without_error_code	0
; without_error_code	1
; without_error_code	2
; without_error_code	3
; without_error_code	4
; without_error_code	5
; without_error_code	6
; without_error_code	7
; with_error_code		8
; without_error_code	9
; with_error_code		10
; with_error_code		11
; with_error_code		12
; with_error_code		13
; with_error_code		14
; without_error_code	15
; without_error_code	16
; with_error_code		17
; without_error_code	18
; without_error_code	19
; without_error_code	20
; without_error_code	21
; without_error_code	22
; without_error_code	23
; without_error_code	24
; without_error_code	25
; without_error_code	26
; without_error_code	27
; without_error_code	28
; without_error_code	29
; with_error_code		30
; without_error_code	31
; ; IRQS
; without_error_code	32
; without_error_code	33
; without_error_code	34
; without_error_code	35
; without_error_code	36
; without_error_code	37
; without_error_code	38
; without_error_code	39
; without_error_code	40
; without_error_code	41
; without_error_code	42
; without_error_code	43
; without_error_code	44
; without_error_code	45
; without_error_code	46
; without_error_code	47
; ; SYSCALLS TRIGGER
; without_error_code	48

; section .bss
; frame_ptr:
; 	resb 4

; section .data
; ; Create isr_vectors array
; isr_vectors:
; %assign i 0
; %rep 49
; 	dd isr_%+i
; %assign i i+1
; %endrep
