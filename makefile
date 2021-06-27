BOOT_DIR = boot
KERNEL_DIR = kernel
LIB_DIR_RC = lib/rclib
LIB_DIR_EFI = lib/refi
OPERATE_BOOT = cd $(BOOT_DIR) && $(MAKE)
OPERATE_KERNEL = cd $(KERNEL_DIR) && $(MAKE)
OPERATE_LIB_RC = cd $(LIB_DIR_RC) && $(MAKE)
OPERATE_LIB_EFI = cd $(LIB_DIR_EFI) && $(MAKE)

debug-test: debug img test
all: RTOS img test

debug:
	$(OPERATE_LIB_RC)
	$(OPERATE_LIB_EFI) 
	$(OPERATE_BOOT) 
	$(OPERATE_KERNEL) RTcore.rm

RTOS:
	$(OPERATE_LIB_RC) librc.a
	$(OPERATE_LIB_EFI) librefi.a
	$(OPERATE_BOOT) BOOTx64.EFI
	$(OPERATE_KERNEL) RTcore.rm
	@echo SUCCESS!
	
img:
	$(OPERATE_KERNEL) img
test:
	$(OPERATE_KERNEL) $@ 

clean:
	$(OPERATE_BOOT) $@ 
	$(OPERATE_KERNEL) $@ 
	$(OPERATE_LIB_RC) $@ 
	$(OPERATE_LIB_EFI) $@ 
	@echo Successfully cleaned!


