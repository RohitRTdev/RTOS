include make-def.mk

#kernel specific files
INCLUDE += -I$(CURDIR)/lib/include/
LDSCRIPTS =$(WORKINGDIR)/ldscripts/kernel_script.ld
LIBRCPATH :=lib/rclib
LIBRC :=$(LIBRCPATH)/librc.a
LIB += $(LIBRC)
TARGET :=RTcore.pe
RTTARGET :=RTcore.rm

include update-rules.mk

build: $(TARGET) 

$(TARGET): $(OBJS) $(LIB)
	@echo "$(BLUE)$(BOLD)$(UPDATE) module $(RTTARGET)$(END)"
	@$(LD) $(LDFLAGS) $^ -o $@ 
	@$(RTBUILDTOOL) $(TARGET) -o $(RTTARGET)

$(LIBRC): $(SUBDEPENDENCY)
	@cd $(LIBRCPATH) && $(MAKE) $(GENCMD) $(BUILD)

clean::
	@cd $(LIBRCPATH) && $(MAKE) clean
	@cd $(LIBGPATH) && $(MAKE) clean

very-clean::
	@cd $(LIBRCPATH) && $(MAKE) very-clean
	@cd $(LIBGPATH) && $(MAKE) very-clean

clean-dep::
	@cd $(LIBRCPATH) && $(MAKE) clean-dep
	@cd $(LIBGPATH) && $(MAKE) clean-dep