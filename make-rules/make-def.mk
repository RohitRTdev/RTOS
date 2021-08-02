CC := x86_64-w64-mingw32-gcc
AS := x86_64-w64-mingw32-as
LD := x86_64-w64-mingw32-ld

override SHELL=/bin/sh


ACTIVEDIR :=$(TOPDIR)/$(subst $(WORKINGDIR)/,,$(CURDIR))
LIBGHEADER =-I$(WORKINGDIR)/lib/include/
INCLUDE = -I$(WORKINGDIR)/include/ -I$(CURDIR)/include/ $(LIBGHEADER) 
CFLAGS =-c -ffreestanding -Wall -mno-red-zone $(INCLUDE)
ASFLAGS =-c    
LDFLAGS =-nostdlib -T$(LDSCRIPTS) --image-base=0 --gc-sections -dll -shared --subsystem $(SUBSYSTEM) -e $(MODULE_ENTRY)
LIBFLAGS :=-rcs
BUILD :=build
LIBGPATH :=$(WORKINGDIR)/lib/glib
LIBG :=$(LIBGPATH)/libg.a
LIB =$(LIBG)
LIBG-SUB-DEPEND-BUILD :=@cd $(LIBGPATH) && $(MAKE) $(GENCMD) $(BUILD)

ifeq ($(GENCMD),gen-dep)
	SUBDEPENDENCY =sub-gen-dep
else
	SUBDEPENDENCY =
endif

ifeq ($(DEBUGMODE),NORMAL)
	SUBDEPENDENCY =
	BUILD :=
endif

ifeq ($(DEBUGMODE),COMPLETE)
	SUBDEPENDENCY =sub-gen-dep
	BUILD :=build
endif


ifeq ($(ACTIVEDIR),$(TOPDIR)/kernel)
    SUBSYSTEM :=0
    MODULE_ENTRY :=kernel_entry
	LDFLAGS +=-s
endif
ifeq ($(ACTIVEDIR),$(TOPDIR)/boot) 
    SUBSYSTEM :=10
    MODULE_ENTRY :=efi_main
endif

ifeq ($(CURDIR),$(LIBGPATH))
	LIBG-SUB-DEPEND-BUILD :=
endif

SRC =$(filter-out include*/* lib/*,$(wildcard *.c *.s */*.c */*.s)) #Collect all .c and .s files
DEPS =$(patsubst %.c,%.d,$(filter %.c,$(SRC)))
OBJS =$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRC))) #Convert to .o files
DEPENDFILE :=depends.inc

default:
	@echo "$(RED)$(BOLD)Please execute a command from the top makefile$(END)"

-include $(DEPENDFILE)


	
#Default rule for generating dependency file
%.d: %.c
	@echo "$(CYAN)Generating $(BOLD)dependency$(END) $(CYAN)for file $(ACTIVEDIR)/$<$(END)"
	@$(CC) $(INCLUDE) -M $< -MF $@ -MT $*.o

#Default rule for compiling .c files
%.o: %.c
	@echo "$(GREEN)$(BOLD)Compiling$(END) $(GREEN)file $(ACTIVEDIR)/$<$(END)"
	@$(CC) $(CFLAGS) $< -o $@

#Default rule for assembling .s files
%.o: %.s
	@echo "$(YELLOW)$(BOLD)Assembling$(END) $(YELLOW)file $(ACTIVEDIR)/$<$(END)"
	@$(AS) $(ASFLAGS) $< -o $@

#Create a dependency file which contains all the header file dependencies
.PHONY: gen-dep build-objects

gen-dep: $(DEPS)
	@echo "$(CYAN)$(BOLD)Creating dependency file for $(ACTIVEDIR)$(END)"
	@rm -rf $(DEPENDFILE)
	@touch $(DEPENDFILE)
	@for dep in $(DEPS); do cat $${dep} >> $(DEPENDFILE) ; done

build-objects: $(OBJS)

#Default rule to build library libg.a(global library for RTOS)
$(LIBG): $(SUBDEPENDENCY)
	$(LIBG-SUB-DEPEND-BUILD)	

.PHONY: clean very-clean sub-gen-dep clean-dep
clean::
	@echo "$(RED)$(BOLD)Deleting intermediate files in $(ACTIVEDIR)$(END)"
	@rm -rf $(OBJS) $(DEPENDFILE) $(DEPS) $(TARGET)

very-clean:: clean
	@echo "$(RED)$(BOLD)Deleting $(TARGET)$(END)"
	@rm -rf $(TARGET) $(RTTARGET)

clean-dep::
	@echo "$(RED)Removing intermediate dependencies at $(CURDIR)$(END)"
	@rm -rf $(DEPS)
