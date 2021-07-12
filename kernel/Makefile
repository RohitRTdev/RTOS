include make-def.mk

#kernel specific files
SRC +=$(wildcard ../utils/*.c ../utils/*.s)
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LIBHEADER += -Ilib/rclib/
LIBRCPATH :=lib/rclib
LIBRC :=$(LIBRCPATH)/librc.a
LIB += $(LIBRC)
TARGET :=RTcore.rm

include update-rules.mk

build: $(TARGET) 

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^ 

clean::
	@cd $(LIBRCPATH) && $(MAKE) clean
	@cd $(LIBGPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBRCPATH) && $(MAKE) very-clean
	@cd $(LIBGPATH) && $(MAKE) very-clean
