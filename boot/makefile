CC = x86_64-w64-mingw32-gcc
LD = x86_64-w64-mingw32-ld
CFLAGS = -ffreestanding  -mno-red-zone -fstack-limit-symbol=0x7ffe0000 -Iinclude/ -c 
LDFLAGS =  -nostdlib  -T ../ldscripts/boot_script.ld --image-base=0 --gc-sections -dll -shared --subsystem 10 -e efi_main -o
LIB = ../lib/refi/librefi.a 
SRC = $(wildcard *.c)
OBJS= *.o
TARGET = BOOTx64.EFI

$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(SRC)
	$(LD) $(LDFLAGS) $@ $(OBJS) $(LIB)
	
.PHONY:
clean:
	rm -rf $(OBJS) *.map 
