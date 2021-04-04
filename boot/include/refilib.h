#ifndef _REFILIB_H_
#define _REFILIB_H_


#include "refi.h"

extern EFI_SYSTEM_TABLE *ST;
extern EFI_BOOT_SERVICES *BS;
extern EFI_RUNTIME_SERVICES *RT;

/*Call this function before using any REFI library functions and also to have ST(Sytem Table), 
BS(Boot Services) and RT(Runtime Services) defined */
void InitLib(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE* SystemTable);
//Print function accepts two tokens as of now, %s(string) and %d(64 bit unsigned integer)
EFI_STATUS printEFI(IN CHAR16 *string, ...);
//Function to report fatal EFI errors
void EFI_FATAL_REPORT(IN CHAR16 *ErrorMessage, IN EFI_STATUS status_code);

//Functions to manipulate strings
UINT64 rstrlen(char *str);
void rstrcat(char *dest, char *src);
INT64 rstrcmp(char *text1, char *text2);
void rstrcpy(char *dest, char *src);

//Analogous string functions for UNICODEINT64 rstrcmp(char *text1, char *text2); enabled
UINT64 wrstrlen(CHAR16 *str);
void wrstrcat(CHAR16 *dest, CHAR16 *src);
INT64 wrstrcmp(CHAR16 *text1, CHAR16 *text2);
void wrstrcpy(CHAR16 *dest, CHAR16 *src);


#endif