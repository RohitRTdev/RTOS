include make-def.mk

CFLAGS +=-I../../include/
TARGET =librefi.a

include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $(TARGET)$(END)"
	@ar $(LIBFLAGS) $@ $^
	
