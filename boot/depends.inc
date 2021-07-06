boot_setup.o: boot_setup.c include/boot/boot_setup.h include/refi/refi.h \
 include/refi/reficheck.h include/refi/refidefs.h include/refi/refienum.h \
 include/refi/refiguid.h include/refi/refistat.h \
 include/refi/refiprotapi.h include/refi/refiprot.h \
 include/refi/refiapi.h include/refi/refitab.h \
 ../lib/refi/include/refilib.h include/boot/boot_structs.h \
 include/boot/primary_loader.h
boot_virtual_setup.o: boot_virtual_setup.c \
 include/boot/boot_virtual_setup.h include/refi/refi.h \
 include/refi/reficheck.h include/refi/refidefs.h include/refi/refienum.h \
 include/refi/refiguid.h include/refi/refistat.h \
 include/refi/refiprotapi.h include/refi/refiprot.h \
 include/refi/refiapi.h include/refi/refitab.h \
 include/boot/boot_structs.h include/boot/primary_loader.h \
 ../lib/refi/include/refilib.h
boot.o: boot.c include/refi/refi.h include/refi/reficheck.h \
 include/refi/refidefs.h include/refi/refienum.h include/refi/refiguid.h \
 include/refi/refistat.h include/refi/refiprotapi.h \
 include/refi/refiprot.h include/refi/refiapi.h include/refi/refitab.h \
 ../lib/refi/include/refilib.h include/boot/primary_loader.h \
 include/boot/basic_font.h include/boot/boot_structs.h \
 include/boot/primary_loader.h include/boot/boot_structs.h \
 include/boot/boot_virtual_setup.h include/boot/modules.h \
 include/boot/boot_setup.h
pe_loader.o: loader/pe_loader.c include/boot/pe.h include/refi/refi.h \
 include/refi/reficheck.h include/refi/refidefs.h include/refi/refienum.h \
 include/refi/refiguid.h include/refi/refistat.h \
 include/refi/refiprotapi.h include/refi/refiprot.h \
 include/refi/refiapi.h include/refi/refitab.h \
 ../lib/refi/include/refilib.h include/boot/primary_loader.h
font_loader.o: loader/font_loader.c include/boot/boot_structs.h \
 include/refi/refi.h include/refi/reficheck.h include/refi/refidefs.h \
 include/refi/refienum.h include/refi/refiguid.h include/refi/refistat.h \
 include/refi/refiprotapi.h include/refi/refiprot.h \
 include/refi/refiapi.h include/refi/refitab.h \
 include/boot/primary_loader.h include/boot/basic_font.h \
 ../lib/refi/include/refilib.h include/boot/boot_structs.h \
 include/boot/primary_loader.h
