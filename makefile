BOOT_DIR = boot
KERNEL_DIR = kernel
LIB_DIR_RC = lib/rclib
LIB_DIR_EFI = lib/refi
OPERATE_BOOT = cd $(BOOT_DIR) && $(MAKE)
OPERATE_KERNEL = cd $(KERNEL_DIR) && $(MAKE)
OPERATE_LIB_RC = cd $(LIB_DIR_RC) && $(MAKE)
OPERATE_LIB_EFI = cd $(LIB_DIR_EFI) && $(MAKE)

all: RTOS img test


RTOS:
	$(OPERATE_LIB_RC) 
	$(OPERATE_LIB_EFI) 
	$(OPERATE_BOOT) 
	$(OPERATE_KERNEL) RTcore.rm
	@echo SUCCESS!
	
img:
	$(OPERATE_KERNEL) $@ 
	@echo SUCCESS!
test:
	$(OPERATE_KERNEL) $@ 

clean:
	$(OPERATE_BOOT) $@ 
	$(OPERATE_KERNEL) $@ 
	$(OPERATE_LIB_RC) $@ 
	$(OPERATE_LIB_EFI) $@ 
	@echo Successfully cleaned!


