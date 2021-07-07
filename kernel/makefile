include ../makefile.default

#kernel compilation flags
SRC +=$(wildcard ../utils/*.c ../utils/*.s)
LDSCRIPTS =../ldscripts/kernel_script.ld
CFLAGS += -Wall
LIBPATH :=../lib/rclib
LIB =$(LIBPATH)/librc.a 
TARGET =RTcore.rm
include ../make-rules/update-rules.inc

build: $(TARGET) 

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(TARGET)$(END)"
	@$(LD) $(LDFLAGS) $@ $^

$(LIB): $(SUBDEPENDENCY)
	@cd $(LIBPATH) && $(MAKE) $(GENCMD) $(BUILD) 

clean::
	@cd $(LIBPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBPATH) &&$(MAKE) very-clean