include ../makefile.default

LDSCRIPTS = ../ldscripts/boot_script.ld
CFLAGS += -fstack-limit-symbol=0x7ffe0000 
LIB = ../lib/refi/librefi.a 

TARGET =BOOTx64.EFI
include ../update-rules.inc

build: build-objects $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) bootloader $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

