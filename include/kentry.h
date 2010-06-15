/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
#ifndef _KENTRY_H_
#define _KENTRY_H_
#define OS_ISR_INTERUPT 0xAF
#endif

#ifdef _INCLUDE_KENTRY_H_SETTINGS_
#define _KSTAND_INC_KI_INFO_H_
#include <kstand.h>
#include <stdint.h>
#include <stddef.h>
#include <terminal.h>
/*Pic Data*/
#define PIC_1_OFFSET 0x20
#define PIC_2_OFFSET 0x2F
#define PIC_1 0x20
#define PIC_2 0xA0
#define PIC_1_DATA (HAL_PIC_1 + 1)
#define PIC_2_DATA (HAL_PIC_2 + 1)
#define PIC_EOI 0x20
#define PIC_INIT 0x10
#define PIC_REMAP 0x11
#define PIC_PIC1_CON 0x04
#define PIC_PIC2_CON 0x02
#define PIC_X86_MODE 0x01

struct gdt_ptr_t
{
 uint16_t size;
 uint32_t offset;
} __attribute__((__packed__));
struct gdt_entry_t
{
 uint16_t limit_low;
 uint16_t base_low;
 uint8_t base_middle;
 uint8_t access;
 uint8_t granularity;
 uint8_t base_high;
}__attribute__((__packed__));

//static void init_pic();
//static void remap_pic(int pic1_offset, int pic2_offset);
//static void init_gdt();
/*gdt manipulation functions*/
/**Gets the address of the GDT table*/
//static void* gdt_gaddr();
/**Installs the gdt table*/
//static void gdt_install(struct gdt_ptr_t *ptr, uint32_t seg);
/**Edits a gdt entry*/
//static void gdt_edit(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, struct gdt_entry_t *gdt);
//static struct multiboot_header* init_memory(void *mbd);
struct gdt_ptr_t *gdt_ptr;


#endif
