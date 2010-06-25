;    Advanced Simulated Filesystem Flora Kernel
;    Copyright (C) 2010  Robert Christian Taylor
;
;    This program is free software; you can redistribute it and/or
;    modify it under the terms of the GNU General Public License
;    as published by the Free Software Foundation; either version 2
;    of the License, or (at your option) any later version.
;
;    This program is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with this program; if not, write to the Free Software
;    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
