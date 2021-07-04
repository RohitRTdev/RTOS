include ../../makefile.default

TARGET =librc.a
include ../../update-rules.inc

build: $(TARGET) | build-objects

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) file $(TARGET)$(END)"
	@ar $(LIB_FLAGS) $@ $(OBJS)		
	