include make-def.mk

TARGET :=libg.a

include update-rules.mk

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $@$(END)"
	@ar $(LIBFLAGS) $@ $^