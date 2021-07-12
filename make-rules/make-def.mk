CC := x86_64-w64-mingw32-gcc
AS := x86_64-w64-mingw32-as
LD := x86_64-w64-mingw32-ld

ACTIVEDIR :=$(TOPDIR)/$(subst $(WORKINGDIR)/,,$(CURDIR))
INCLUDE = -Iinclude/ $(LIB_HEADER)
LIBHEADER =-I$(WORKINGDIR)/lib/glib/
CFLAGS =-c -ffreestanding -mno-red-zone $(INCLUDE)
ASFLAGS =-c    
LDFLAGS =-nostdlib -T$(LDSCRIPTS) --image-base=0 --gc-sections -dll -shared --subsystem $(SUBSYSTEM) -e $(MODULE_ENTRY)
LIBFLAGS :=-rcs
BUILD :=build
LIBGPATH :=$(WORKINGDIR)/lib/glib
LIBG :=$(LIBGPATH)/glib.a
LIB =$(LIBG)
LIBG-SUB-DEPEND-BUILD :=@cd $$(LIBGPATH) && $$(MAKE) $$(GENCMD) $$(BUILD)

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
LDFLAGS +=-o

SRC =$(filter-out include*/*.*,$(wildcard *.c *.s */*.c */*.s)) #Collect all .c and .s files
DEPS =$(patsubst %.c,%.d,$(filter %.c,$(SRC)))
OBJS =$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRC))) #Convert to .o files
DEPENDFILE :=depends.inc

default:
	@echo "$(RED)$(BOLD)Please execute a command from the top makefile$(END)"

-include $(DEPENDFILE)

#Create a dependency file which contains all the header file dependencies
gen-dep: $(DEPS)
	@echo "$(CYAN)$(BOLD)Creating dependency file for $(ACTIVEDIR)$(END)"
	@touch $^
	@cat $(DEPS) > $(DEPENDFILE)
	@rm -rf $(DEPS)

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

build-objects: $(OBJS)

#Default rule to build library libg.a(global library for RTOS)
$(LIBG): $(SUBDEPENDENCY)
	$(LIBG-SUB-DEPEND-BUILD)	

.PHONY: clean very-clean sub-gen-dep
clean::
	@echo "$(RED)$(BOLD)Deleting intermediate files in $(ACTIVEDIR)$(END)"
	@rm -rf $(OBJS) $(DEPENDFILE) $(DEPS)

very-clean:: clean
	@echo "$(RED)$(BOLD)Deleting $(TARGET)$(END)"
	@rm -rf $(TARGET)
