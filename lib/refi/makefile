include ../../makefile.default

TARGET =librefi.a
include ../../update-rules.inc
build: $(TARGET)

$(TARGET): build-objects
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $(TARGET)$(END)"
	@ar $(LIBFLAGS) $@ $(OBJS)
	
