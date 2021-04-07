CC = x86_64-w64-mingw32-gcc
LD = x86_64-w64-mingw32-ld
INCLUDE = -Iinclude -I../lib/rclib/include
LDSCRIPTS = ../ldscripts/kernel_script.ld
CFLAGS = -ffreestanding  -mno-red-zone -fPIC -Wall -Wno-varargs  $(INCLUDE) -c 
LDFLAGS =  -nostdlib -T $(LDSCRIPTS) --image-base=0 --gc-sections -shared --subsystem 0 -e kernel_entry -o
LIB = ../lib/rclib/librc.a
DIR := $(filter-out $(wildcard *.*) include ,$(wildcard *))
SRC := $(wildcard $(foreach dir,$(DIR),$(dir)/*[.c|.s]) *.c *.s ../utils/*.c ../utils/*.s)
OBJS := $(addsuffix .o,$(foreach path, $(basename $(SRC)),$(lastword $(subst /, ,$(path)))))
TARGET = RTcore.rm 
mount = EFI/BOOT
IMG = ../resources/RTOS_1.0.iso
TEST= qemu-system-x86_64
CPU = Nehalem
BIOS= ../resources/OVMF.fd
FONT = ../resources/*.psf
var := $(shell sudo losetup -f)

$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(SRC)
	$(LD) $(LDFLAGS) $@ $(OBJS) $(LIB)

img: ../boot/BOOTx64.EFI
	sudo losetup --offset 1048576 --sizelimit 52428800 $(var) $(IMG)
	mkdir mnt/
	sudo mount $(var) mnt/
	sudo cp $^ mnt/$(mount)
	sudo cp $(TARGET) $(FONT) mnt/
	sudo umount mnt/
	rm -rf mnt/
	sudo losetup -d $(var)

test: $(IMG)
	$(TEST) -cpu $(CPU) -bios $(BIOS) -drive file=$(IMG),if=ide

.PHONY: clean
clean: 
	rm -rf *.o *.su
