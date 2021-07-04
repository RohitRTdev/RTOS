include ../../makefile.default

TARGET =librc.a
include ../../update-rules.inc

build: $(TARGET) | build-objects

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $(TARGET)$(END)"
	@ar $(LIBFLAGS) $@ $(OBJS)		
	