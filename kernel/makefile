include ../makefile.default

#kernel compilation flags
LIB_HEADER =../lib/rclib/include
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LDFLAGS += -s
LIB = ../lib/rclib/librc.a 
TARGET =RTcore.rm
include ../update-rules.inc

build: build-objects $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^