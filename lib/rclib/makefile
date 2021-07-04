include ../../makefile.default

TARGET =librc.a
include ../../update-rules.inc

build: build-objects $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) file $(TARGET)$(END)"
	@ar $(LIB_FLAGS) $@ $(OBJS)		
	