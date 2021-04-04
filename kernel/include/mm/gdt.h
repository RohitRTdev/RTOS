#ifndef _GDT_H_
#define _GDT_H_

#include <mm/phyMemstructs.h>

#pragma pack(1)

#define SYSTEM_DESCRIPTOR 0
#define USER_SEGMENT 1
#define RING0 0
#define RING1 1
#define RING2 2
#define RING3 3
#define sixtyfourbitmode 1
#define compatibiltitymode 0
#define normalopsize 0
#define longopsize 1
#define CODE_SEG 1
#define DATA_SEG 0
#define NONCONFORMINGCODESEG 0
#define SEGMENTPRESENT 1

#define GDT_DEFAULT_SIZE BLOCK_SIZE(4096)


typedef struct __attribute__((__packed__)){
    uint16_t limit;
    uint64_t base_address;    
}gdt_register;
typedef struct __attribute__((__packed__)){
    uint16_t seg_limit;
    uint16_t base_address;
    uint8_t  base;
    uint16_t type : 4;
    uint16_t des_type : 1;
    uint16_t dpl : 2;
    uint16_t seg_present : 1;
    uint16_t seg_limit_rem : 4;
    uint16_t avl : 1;
    uint16_t code_seg_bit : 1;
    uint16_t def_op_size : 1;
    uint16_t granularity : 1;
    uint8_t  base_rem;
}segment_descriptor;

#endif