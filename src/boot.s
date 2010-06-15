;/*
;###############################################################################################
;# Copyright 2010 Robert Christian Taylor. All rights reserved.                                #
;#                                                                                             #
;# Redistribution and use in source and binary forms, with or without modification, are        #
;# permitted provided that the following conditions are met:                                   #
;#                                                                                             #
;#  1. Redistributions of source code must retain the above copyright notice, this list of     #
;#     conditions and the following disclaimer.                                                #
;#                                                                                             #
;# THIS SOFTWARE IS PROVIDED BY Robert Christian Taylor ``AS IS'' AND ANY EXPRESS OR IMPLIED   #
;# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND    #
;# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Robert Christian Taylor  #
;# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR      #
;# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR    #
;# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    #
;# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING          #
;# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF        #
;# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                  #
;#                                                                                             #
;# The views and conclusions contained in the software and documentation are those of the      #
;# authors and should not be interpreted as representing official policies, either expressed   #
;# or implied, of Robert Christain Taylor.                                                     #
;###############################################################################################
;*/
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