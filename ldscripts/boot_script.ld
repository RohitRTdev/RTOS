ENTRY(efi_main)
OUTPUT_FORMAT(pei-x86-64)

SECTIONS{
    . = SIZEOF_HEADERS;
    . = ALIGN(__section_alignment__); 
    
    .text __image_base__ + (__section_alignment__ < 0x1000? . : __section_alignment__) : {
        *(.text)
    }
    .data ALIGN(__section_alignment__) : {
        *(.data)
        *(.rdata*)
    }   
    .bss ALIGN(__section_alignment__) : {
        *(.bss)
        *(.sbss)
        *(.COMMON)
    }   
    .reloc ALIGN(__section_alignment__) : {
        *(.reloc)
    }
    .edata ALIGN(__section_alignment__) : {
        *(.edata)
    }
    .idata ALIGN(__section_alignment__) : {
        *(.idata)
    }
    /DISCARD/ : {
        *(.drectve)
        *(.xdata)
        *(.pdata)
    }

}