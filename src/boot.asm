; Multiboot-compliant entry point for GRUB
BITS 32

section .multiboot
align 4
    dd 0x1BADB002               ; magic
    dd 0x00000003               ; flags: align modules + mem info
    dd -(0x1BADB002 + 0x00000003)

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global start
extern kmain

start:
    cli
    mov esp, stack_top
    push ebx                     ; multiboot info pointer
    push eax                     ; multiboot magic
    call kmain
.hang:
    hlt
    jmp .hang

section .note.GNU-stack noalloc noexec nowrite progbits
