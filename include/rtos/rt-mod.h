#ifndef __RTMOD_H__
#define __RTMOD_H__

#include <rtos/rtypes.h>

#define RT_SIGN "_RTMOD_"

#pragma pack(1)

#define IMAGE_REL_BASED_DIR64 10

typedef struct{
	char sect_name[8];
	uint64_t ptr_to_sect;
	uint64_t size_of_sect;
	uint64_t virtual_address;
}rt_sect_info;

typedef struct{
	char rt_sign[8];
	uint64_t image_size;
	uint64_t image_entry;
	rt_sect_info rt_sections[4];
}rt_hdr;

#define SIZE_OF_RT_SIGN 8
#define TOTAL_SECTIONS 4

#pragma pack()

#endif