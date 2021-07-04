TOPDIR =RTOS
BOOT_DIR =boot
KERNEL_DIR =kernel
LIB_DIR_RC =lib/rclib
LIB_DIR_EFI =lib/refi
OPERATE_BOOT = cd $(BOOT_DIR) && $(MAKE)
OPERATE_KERNEL = cd $(KERNEL_DIR) && $(MAKE)
OPERATE_LIB_RC = cd $(LIB_DIR_RC) && $(MAKE)
OPERATE_LIB_EFI = cd $(LIB_DIR_EFI) && $(MAKE)
VERSION :=1.0
OS :=RTOS_$(VERSION)

include makefile.img
include colors.inc

export TOPDIR

debug: debug-compile build-img test
build: RTOS build-img

debug-compile:
	$(OPERATE_LIB_RC)
	$(OPERATE_LIB_EFI) 
	$(OPERATE_BOOT) 
	$(OPERATE_KERNEL) RTcore.rm

RTOS:
	@echo "$(RED)$(BOLD)Building rclib!$(END)"
	$(OPERATE_LIB_RC) librc.a
	@echo "$(RED)$(BOLD)Building refilib!$(END)"
	$(OPERATE_LIB_EFI) librefi.a
	@echo "$(RED)$(BOLD)Building bootloader!$(END)"
	$(OPERATE_BOOT) BOOTx64.EFI
	@echo "$(RED)$(BOLD)Building kernel!$(END)"
	$(OPERATE_KERNEL) RTcore.rm
	@echo "$(GREEN)$(BOLD)Components build successful$(END)"
	
build-img: $(OS_IMG) 
	
$(OS_IMG): $(BOOT_IMAGE) $(RT_CORE)
	@echo $(ECHO_FLAGS) "$(RED)Starting RTOS image build!"
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
	@echo $(ECHO_FLAGS) "$(GREEN)$(OS) image built successfully!"
test:
	@echo "$(YELLOW)Loading qemu emulator$(END)"
	$(DEFAULT_TEST)

clean:
	$(OPERATE_BOOT) $@ 
	$(OPERATE_KERNEL) $@
	$(OPERATE_LIB_RC) $@ 
	$(OPERATE_LIB_EFI) $@ 
	@echo $(RED)$(BOLD)Removed intermediate files$(END)"


