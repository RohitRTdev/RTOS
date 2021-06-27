CC = x86_64-w64-mingw32-gcc
AS = x86_64-w64-mingw32-as
LD = x86_64-w64-mingw32-ld
CFLAGS = -ffreestanding  -mno-red-zone -fstack-limit-symbol=0x7ffe0000 -Iinclude/ 
LDFLAGS =  -nostdlib  -T ../ldscripts/boot_script.ld --image-base=0 --gc-sections -dll -shared --subsystem 10 -e efi_main -o
LIB = ../lib/refi/librefi.a 
SRCC = $(wildcard *.c)
SRCS = $(wildcard *.s)
OBJS= $(patsubst %.c, %.o, $(SRCC))
OBJS+= $(patsubst %.s, %.o, $(SRCS))
TARGET = BOOTx64.EFI

$(TARGET): $(OBJS) $(LIB)
	$(LD) $(LDFLAGS) $@ $(OBJS) $(LIB)
	
	
.PHONY:
clean:
	rm -rf *.o *.map 
