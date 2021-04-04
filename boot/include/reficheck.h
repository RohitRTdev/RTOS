#ifndef _REFI_CHECK_H_
#define _REFI_CHECK_H_


#if !(defined(__MINGW64__))
#error Use MINGW64 compiler to correctly compile
#endif
#if !(__GNUC__ > 7 || (__GNUC_MINOR__ == 3 && __GNUC_PATCHLEVEL__ >= 0))
#error Use MINGW64 version 7.3 or greater
#endif
#endif 