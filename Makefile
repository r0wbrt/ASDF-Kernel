#/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
CC=/usr/cross/bin/i386-elf-gcc
INCLUDE = ./include
CFLAGS = -I$(INCLUDE) -Wextra  -Wall -nostdlib -nostartfiles -nodefaultlibs -c -O2 
ASSEMBLER=nasm
ASFLAGS = -f elf
SRC = ./src/
LINKER = /usr/cross/bin/i386-elf-ld
OBJDIR = ./objdir/
LINKLD = ./link.ld
KOUT = ./kernel.elf
GRUB = ./other/
EXTRA = ./other/
KIMG = ./k.img
BOCHS = "/cygdrive/c/Program Files/Bochs-2.4.5/bochs.exe" 
SOURCE = $(SRC)kentry.c $(SRC)terminal.c $(SRC)string.c $(SRC)stddef.c $(SRC)kqueue.c\
$(INCLUDE)/kentry.h $(INCLUDE)/terminal.h $(INCLUDE)/string.h $(INCLUDE)/stddef.h $(INCLUDE)/inlineasm.h $(INCLUDE)/kqueue.h
SOURCES = $(SRC)boot.s
COBJECTS = kentry.o terminal.o string.o stddef.o kqueue.o
SOBJECTS = boot.o
	
all: $(SOURCE) $(COBJECTS) $(SOBJECTS) $(SOURCES)
	$(LINKER) -T$(LINKLD) $(COBJECTS) $(SOBJECTS) -o $(KOUT)
%.o: $(SRC)%.c
	$(CC) $(CFLAGS) $< -o $@
%.o: $(SRC)%.s
	$(ASSEMBLER) $(ASFLAGS) $< -o $@ 
clean:
	\rm $(COBJECTS) $(SOBJECTS) $(KOUT) $(KIMG) 
testimg:
	cat $(GRUB)stage1 $(GRUB)stage2 $(EXTRA)pad  $(KOUT)> $(KIMG)
test: 
	cat $(GRUB)stage1 $(GRUB)stage2 $(EXTRA)pad  $(KOUT)> $(KIMG)
	$(BOCHS)
