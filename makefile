include colors.inc

TOPDIR =RTOS
WORKINGDIR =$(shell pwd)\
MAKEFLAGSAVE =$(MAKEFLAGS)
MAKEFLAGS +=--no-print-directory
BOOT_DIR =boot
KERNEL_DIR =kernel
LIB_DIR_RC =lib/rclib
LIB_DIR_EFI =lib/refi
OPERATE_BOOT = cd $(BOOT_DIR) && $(MAKE)
OPERATE_KERNEL = cd $(KERNEL_DIR) && $(MAKE)
VERSION :=1.0
OS :=RTOS_$(VERSION)

include image-rules.inc

export TOPDIR WORKINGDIR

default: 
	@echo "$(RED)Execute $(BOLD)make build$(END) $(RED)to get started$(END)"

debug: debug-compile build-img test
build: RTOS

debug-compile:
	$(OPERATE_KERNEL) build MAKEFLAGS=$(MAKEFLAGSAVE)

RTOS:
	@echo "$(RED)$(BOLD)Building bootloader!$(END)"
	@$(OPERATE_BOOT) build
	@echo "$(RED)$(BOLD)Building kernel!$(END)"
	@$(OPERATE_KERNEL) build
	@echo "$(GREEN)$(BOLD)Components build successful$(END)"
	
#Used only for testing purposes(Do not call this option in make)	
build-img: $(OS_IMG) 
	
$(OS_IMG): $(BOOT_IMAGE) $(RT_CORE)
	@echo "$(RED)Starting RTOS image build!$(END)"
	$(eval var := $(shell sudo losetup -f))
	sudo losetup --offset 1048576 --sizelimit 52428800 $(var) $@
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
	@$(OPERATE_LIB_RC) $@ 
	@$(OPERATE_LIB_EFI) $@ 
	@echo "$(GREEN)$(BOLD)Removed intermediate files$(END)"

very-clean: 
	@$(OPERATE_BOOT) $@ 
	@$(OPERATE_KERNEL) $@
	@$(OPERATE_LIB_RC) $@ 
	@$(OPERATE_LIB_EFI) $@ 
	@echo "$(GREEN)$(BOLD)Restored initial directory structure$(END)"


