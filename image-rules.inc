#Default mount point for EFI files
mount = mnt
mount_dir = $(mount)/EFI $(mount)/EFI/BOOT/ $(mount)/Modules $(mount)/Fonts

#Image directory
RESC_DIR := resources
OS_IMG := $(RESC_DIR)/$(OS).iso

#Final images
BOOT_IMAGE :=boot/BOOTx64.EFI
RT_CORE :=kernel/RTcore.rm

#Default flags for default test
TEST := qemu-system-x86_64
CPU := Nehalem
BIOS := $(RESC_DIR)/OVMF.fd
FONT := $(RESC_DIR)/*.psf
SYSFILES := SystemFiles

define DEFAULT_TEST
    $(TEST) -cpu $(CPU) -bios $(BIOS) -drive file=$(OS_IMG),format=raw,if=ide
endef
