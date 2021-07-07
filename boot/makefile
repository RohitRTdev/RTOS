include ../makefile.default

LDSCRIPTS = ../ldscripts/boot_script.ld
CFLAGS += -fstack-limit-symbol=0x7ffe0000 
LIBPATH :=../lib/refi
LIB =$(LIBPATH)/librefi.a 


TARGET =BOOTx64.EFI
include ../make-rules/update-rules.inc

build: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) bootloader $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

$(LIB): $(SUBDEPENDENCY) 
	@cd $(LIBPATH) && $(MAKE) $(GENCMD) $(BUILD)

clean::
	@cd $(LIBPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBPATH) &&$(MAKE) very-clean