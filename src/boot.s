;/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
global entry
extern kentry

MODULEALIGN equ  1<<0
MEMINFO  equ  1<<1
FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ    0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

_asm_kvb equ 0xC0000000
_asm_kpn equ (_asm_kvb >> 22)

section .data
align 0x1000
_asm_bpg:
    dd 0x00000083
    times (_asm_kpn - 1) dd 0
    dd 0x00000083
    times (1024 - _asm_kpn - 1) dd 0
    section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
_asm_kistck_sz  equ 0x4000
entry:
    mov ecx, (_asm_bpg - _asm_kvb)
    mov cr3, ecx                                     
    mov ecx, cr4
    or ecx, 0x00000010                          
    mov cr4, ecx
    mov ecx, cr0
    or ecx, 0x80000000                          
    mov cr0, ecx
    lea ecx, [_asm_erc]
    jmp ecx                                                    
 
_asm_erc:
    mov esp, _asm_kistck+_asm_kistck_sz 
    mov ecx, (_asm_bpg)
    push ecx    
    push eax 
    push ebx
    call  kentry
    
_asm_hlt_lp:
    hlt  
    jmp _asm_hlt_lp
    
section .bss
align 32
_asm_kistck:
    resb _asm_kistck_sz