include make-def.mk

INCLUDE += -I../include/
TARGET :=libg.a

include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $@$(END)"
	@ar $(LIBFLAGS) $@ $^