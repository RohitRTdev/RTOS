ENTRY(kernel_entry)
OUTPUT_FORMAT(pei-x86-64)

SECTIONS{
    . = SIZEOF_HEADERS;
    . = ALIGN(__section_alignment__); 
    
    .text __image_base__ + (__section_alignment__ < 0x1000? . : __section_alignment__) : {
        *(.text)
    }
    /* KEEP() ensures linker doesn't remove data even if it is not referenced anywhere in the code */
    /* This might be useful if some other module, that is not part of the kernel is referencing that data 
        but not the kernel itself */
    .data ALIGN(__section_alignment__) : {
        *(.data)
        KEEP(*(.data))                    
        *(.rdata*)
        KEEP(*(.rdata))
    }   
    .bss ALIGN(__section_alignment__) : {
        *(.bss)
        KEEP(*(.bss))
        *(.sbss)
        KEEP(*(.sbss))
        *(.COMMON)
        KEEP(*(.COMMON))
    }   
    .reloc ALIGN(__section_alignment__) : {
        *(.reloc)
    }
    /* .edata and .idata are not of use to us as they are included for dll support 
        which is not yet implemented in RTOS */
    
    /DISCARD/ : {
        *(.drectve)
        *(.xdata)
        *(.pdata)
        *(.idata)
        *(.edata)
    }

}