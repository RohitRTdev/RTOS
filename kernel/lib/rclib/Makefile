include make-def.mk

INCLUDE += -I../include/
TARGET =librc.a
include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $(TARGET)$(END)"
	@ar $(LIBFLAGS) $@ $^		
	