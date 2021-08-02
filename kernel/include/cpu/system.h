#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <rtos/rtypes.h>
#include <kernel/utils.h>

#define READ 0
#define WRITE 1

//CR0 
#define PE _BV(0)
#define MP _BV(1)
#define EM _BV(2)
#define TS _BV(3)
#define ET _BV(4)
#define NE _BV(5)
#define WP _BV(16)
#define AM _BV(18)
#define NW _BV(29)
#define CD _BV(30)
#define PG _BV(31)

//CR3 
#define PWT _BV(3)
#define PCD _BV(4)

//CR4
#define VME        _BV(0)
#define PVI        _BV(1)
#define TSD        _BV(2)
#define DE         _BV(3)
#define PSE        _BV(4)
#define PAE        _BV(5)
#define MCE        _BV(6)
#define PGE        _BV(7)
#define PCE        _BV(8)
#define OSFXSR     _BV(9) 
#define OSXMMEXCPT _BV(10)
#define FSGSBASE   _BV(16)
#define OSXSAVE    _BV(18)

uint64_t _cr_0(uint64_t val, boolean op);
uint64_t _cr_2(uint64_t val, boolean op);
uint64_t _cr_3(uint64_t val, boolean op);
uint64_t _cr_4(uint64_t val, boolean op);
uint64_t _cr_8(uint64_t val, boolean op);

#define CR(index, val, op) _cr_##index(val, op)  //Valid operations are read and write

void halt_system() __attribute__((noreturn));

#endif