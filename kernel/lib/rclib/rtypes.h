#ifndef _R_TYPES_H_
#define _R_TYPES_H_

/* RTOS presently compiles only with Mingw64 */

#if !defined(__MINGW64__)
        #error Use MINGW64 to compile RTOS modules and programs!
#endif             
#if defined(__MINGW64__)          

            typedef char int8_t;
            typedef unsigned char uint8_t;
            typedef short int int16_t;
            typedef unsigned short int uint16_t;
            typedef int int32_t;
            typedef unsigned int uint32_t;
            typedef long long int64_t;  
            typedef unsigned long long uint64_t;
            typedef uint64_t size_t;           


#ifdef UNICODE

#define RTEXT(str) L##str

#else

#define RTEXT(str) str

#endif

typedef uint8_t CHAR8;
typedef uint16_t wchar_t;

typedef uint8_t boolean;

#define NULL ((void*)0)
#define true ((boolean)1)
#define false ((boolean)0)

typedef uint64_t size_t;
typedef uint64_t* uintptr_t;
typedef int64_t*  intptr_t;

#define atomic _Atomic

#endif /* MINGW64 */
#endif /* _R_TYPES_H_ */