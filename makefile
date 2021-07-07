include make-rules/colors.inc

TOPDIR =RTOS
WORKINGDIR =$(shell pwd)
MAKEFLAGSAVE =$(MAKEFLAGS)
MAKEFLAGS +=--no-print-directory
BOOT_DIR =boot
KERNEL_DIR =kernel
OPERATE_BOOT = cd $(BOOT_DIR) && $(MAKE)
OPERATE_KERNEL = cd $(KERNEL_DIR) && $(MAKE)
VERSION :=1.0
OS :=RTOS_$(VERSION)

DEBUGTARGET :=$(BOOT_DIR)
GENCMD := $(findstring gen-dep,$(MAKECMDGOALS))
DEBUGMODE :=NORMAL
INVALID :=

include make-rules/image-rules.inc

export TOPDIR WORKINGDIR GENCMD INVALIDOPTION


#Catch environment errors
ifeq ($(findstring debug,$(MAKECMDGOALS)),)
	GENDEP_MESSAGE :=@echo "$(RED)Do not call this method directly. Use $(BOLD)make debug gen-dep$(END)$(RED) or $(BOLD)make build$(END)"
else
	GENDEP_MESSAGE :=@echo "$(GREEN)$(BOLD)Generated all dependency files$(END)"
endif

ifeq ($(findstring $(DEBUGMODE),NORMAL COMPLETE),)
$(error DEBUGMODE=$(DEBUGMODE) is an invalid option)
endif

.PHONY: default debug build debug-compile RTOS build-img clean test very-clean gen-dep
default: 
	@echo "$(RED)Execute $(BOLD)make build$(END) $(RED)to get started$(END)"


#Use make debug to only work with the DEBUGTARGET
debug: debug-compile
build: RTOS

debug-compile:
	@echo "$(RED)$(BOLD)Starting Debugging for $(DEBUGTARGET)$(END)"
	@cd $(DEBUGTARGET) && $(MAKE) $(GENCMD) build MAKEFLAGS=$(MAKEFLAGSAVE) DEBUGMODE=$(DEBUGMODE)

RTOS:
	@echo "$(RED)$(BOLD)Building bootloader!$(END)"
	@$(OPERATE_BOOT) gen-dep build GENCMD=gen-dep
	@echo "$(RED)$(BOLD)Building kernel!$(END)"
	@$(OPERATE_KERNEL) gen-dep build GENCMD=gen-dep
	@echo "$(GREEN)$(BOLD)Components build successful$(END)"
	
#Used only for testing purposes(Do not call this option in make)	
build-img: $(OS_IMG) 
	
$(OS_IMG): $(BOOT_IMAGE) $(RT_CORE)
	@echo "$(RED)Starting RTOS image build!$(END)"
	$(eval var := $(shell sudo losetup -f))
	sudo losetup --offset 1048576 --sizelimit 104857600 $(var) $@
	mkdir -p $(mount) 
	sudo mount $(var) $(mount)
	sudo mkdir -p $(mount_dir)
	sudo cp $(BOOT_IMAGE) $(mount)/EFI/BOOT
	sudo cp $(RT_CORE) $(mount)/Modules
	sudo cp $(FONT) $(mount)/Fonts
	sudo losetup -d $(var)
	sudo umount $(mount)
	rm -rf $(mount)
	@echo "$(GREEN)$(OS) image built successfully!"

test:
	@echo "$(YELLOW)Loading qemu emulator$(END)"
	$(DEFAULT_TEST)

clean:
	@$(OPERATE_BOOT) $@ 
	@$(OPERATE_KERNEL) $@
	@echo "$(GREEN)$(BOLD)Removed intermediate files$(END)"

very-clean: 
	@$(OPERATE_BOOT) $@ 
	@$(OPERATE_KERNEL) $@
	@echo "$(GREEN)$(BOLD)Restored initial directory structure$(END)"

gen-dep:
	$(GENDEP_MESSAGE)	
