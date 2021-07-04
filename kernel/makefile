include ../makefile.default

#kernel compilation flags
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LIB = ../lib/rclib/librc.a 
TARGET =RTcore.rm
include ../update-rules.inc

build: $(TARGET) | build-objects 

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^