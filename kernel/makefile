include ../makefile.default

#kernel compilation flags
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LIBPATH :=../lib/rclib
LIB =$(LIBPATH)/librc.a 
TARGET =RTcore.rm
include ../update-rules.inc

build: $(TARGET) 

$(TARGET): build-objects $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

$(LIB): $(SUBDEPENDENCY)
	@cd $(LIBPATH) && $(MAKE) $(GENCMD) build 

clean::
	@cd $(LIBPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBPATH) &&$(MAKE) very-clean