include make-def.mk

LDSCRIPTS = ../ldscripts/boot_script.ld
CFLAGS += -fstack-limit-symbol=0x7ffe0000 
LIBHEADER += -Ilib/refilib/
LIBREFIPATH :=lib/refilib
LIBREFI :=$(LIBREFIPATH)/librefi.a
LIB +=$(LIBREFI) 
TARGET =BOOTx64.EFI

include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) bootloader $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

$(LIBREFI): $(SUBDEPENDENCY) 
	@cd $(LIBREFIPATH) && $(MAKE) $(GENCMD) $(BUILD)

clean::
	@cd $(LIBREFIPATH) && $(MAKE) clean
	@cd $(LIBGPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBREFIPATH) && $(MAKE) very-clean
	@cd $(LIBGPATH) && $(MAKE) very-clean
