#ifndef _UTILS_H_
#define _UTILS_H_

#include <mm/gdt.h>


#define _BV(val) (1 << val)
#define _BC(val) (~(1 << val))
#define _bit_set(val, bit) (val |= _BV(bit))
#define _bit_clear(val, bit) (val &= _BC(bit))
#define _set_bit_check(val, bit) ((val & _BV(bit)) != 0)
#define _clear_bit_check(val, bit) ((val & _BV(bit)) == 0) 


void _cli();
void _sti();
void load_gdt(gdt_register *gdt_reg);
void store_gdt(gdt_register *gdt_reg);



#endif