include make-def.mk

INCLUDE +=-I$(CURDIR)/lib/include/
LDSCRIPTS = $(WORKINGDIR)/ldscripts/boot_script.ld
CFLAGS += -fstack-limit-symbol=0x7ffe0000 
LIBREFIPATH =lib/refilib
LIBREFI = $(LIBREFIPATH)/librefi.a
LIB +=$(LIBREFI) 
TARGET =BOOTx64.EFI

include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) bootloader $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $^ -o $@

$(LIBREFI): $(SUBDEPENDENCY) 
	@cd $(LIBREFIPATH) && $(MAKE) $(GENCMD) $(BUILD)

clean::
	@cd $(LIBREFIPATH) && $(MAKE) clean
	@cd $(LIBGPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBREFIPATH) && $(MAKE) very-clean
	@cd $(LIBGPATH) && $(MAKE) very-clean

clean-dep::
	@cd $(LIBREFIPATH) && $(MAKE) clean-dep
	@cd $(LIBGPATH) && $(MAKE) clean-dep