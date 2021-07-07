include ../../makefile.default

TARGET =librefi.a
include ../../make-rules/update-rules.inc
build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BOLD)$(UPDATE) library $(TARGET)$(END)"
	@ar $(LIBFLAGS) $@ $^
	
