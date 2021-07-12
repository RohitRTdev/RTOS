#ifndef _GLIB_TYPES_H_
#define _GLIB_TYPES_H_

/* This header gives a neutral type definition for the global library */
#if defined(__MINGW64__) 
	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long long int u64;
	typedef char i8;
	typedef short int i16;
	typedef int i32;
	typedef long long int i64;
	typedef u8 bool;
	typedef u64 st;
	typedef u16 wchar;

	#define false ((bool)0)
	#define true  ((bool)1)
#endif

#define MAXCHARCOUNT 100
#define NULL ((void*)0)

#endif