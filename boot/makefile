include ../makefile.default

LDSCRIPTS = ../ldscripts/boot_script.ld
CFLAGS += -fstack-limit-symbol=0x7ffe0000 
LDFLAGS += -T$(LDSCRIPTS) 
LIB = ../lib/refi/librefi.a 

TARGET = BOOTx64.EFI

build:
	@echo Building Bootloader!
	make -C $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(LD) $(LDFLAGS) $@ $(OBJS) $(LIB)
	
	
.PHONY:
clean:
	rm -rf *.o *.map 
