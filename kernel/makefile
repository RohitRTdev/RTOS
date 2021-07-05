include ../makefile.default

#kernel compilation flags
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LIBPATH :=../lib/rclib
LIB =$(LIBPATH)/librc.a 
TARGET =RTcore.rm
include ../update-rules.inc

build: $(TARGET) | build-objects 

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

$(LIB):
	cd $(LIBPATH) && $(MAKE) build