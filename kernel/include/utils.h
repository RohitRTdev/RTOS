#ifndef _UTILS_H_
#define _UTILS_H_

#include <mm/gdt.h>


#define _BV(val) (1 << val)

void _cli();
void _sti();
void load_gdt(gdt_register *gdt_reg);
void store_gdt(gdt_register *gdt_reg);

#endif