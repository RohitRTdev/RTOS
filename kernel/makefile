CC = x86_64-w64-mingw32-gcc
AS = x86_64-w64-mingw32-as
LD = x86_64-w64-mingw32-ld
INCLUDE = -Iinclude -I../lib/rclib/include
LDSCRIPTS = ../ldscripts/kernel_script.ld
CFLAGS = -ffreestanding  -mno-red-zone -fPIC -Wall $(INCLUDE)
LDFLAGS =  -nostdlib -T $(LDSCRIPTS) --image-base=0 --gc-sections -s -shared --subsystem 0 -e kernel_entry -o
LIB = ../lib/rclib/librc.a
DIR := $(filter-out $(wildcard *.*) include ,$(wildcard *))
SRC := $(wildcard $(foreach dir,$(DIR),$(dir)/*[.c|.s]) *.c *.s ../utils/*.c ../utils/*.s)
OBJS := $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRC)))
TARGET = RTcore.rm 
mount = EFI/BOOT
IMG = ../resources/RTOS_1.0.iso
TEST= qemu-system-x86_64
CPU = Nehalem
BIOS= ../resources/OVMF.fd
FONT = ../resources/*.psf
BOOT_IMAGE = ../boot/BOOTx64.EFI
SYSFILES = SystemFiles

debug: 

$(TARGET): $(OBJS) $(LIB) 
	$(LD) $(LDFLAGS) $@ $^

#Used only for debug
img: $(BOOT_IMAGE)
	$(eval var := $(shell sudo losetup -f))
	sudo losetup --offset 1048576 --sizelimit 52428800 $(var) $(IMG)
	mkdir -p mnt/ 
	sudo mount $(var) mnt/
	sudo mkdir -p mnt/EFI mnt/EFI/BOOT/ mnt/Modules mnt/Fonts
	sudo cp $^ mnt/$(mount)
	sudo cp *.rm mnt/Modules
	sudo cp $(FONT) mnt/Fonts
	sudo losetup -d $(var)
	sudo umount mnt
	rm -rf mnt/

test: $(IMG)
	$(TEST) -cpu $(CPU) -bios $(BIOS) -drive file=$(IMG),format=raw,if=ide

.PHONY: clean
clean:
	rm -rf $(OBJS) *.su
