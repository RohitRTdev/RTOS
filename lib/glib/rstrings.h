#ifndef _R_STRINGS_H_
#define _R_STRINGS_H_

#include <rtos/rtypes.h>
#include <rtos/defs.h>

uint64_t rstrlen(char *str);
int64_t rstrcmp(char *dest, char *src);
void rstrcpy(char *dest, char *src);
void rstrcat(char *dest, char *src);

void reverse_str(char *str);
void rtostring(uint64_t value, char *str);
void rfloatTostring(double value, char *str, uint8_t precision);
int8_t rtoint(char ch);
boolean risdigit(char ch);



uint64_t wrstrlen(wchar_t *str);
int64_t wrstrcmp(wchar_t *dest, wchar_t *src);
void wrstrcpy(wchar_t *dest, wchar_t *src);
void wrstrcat(wchar_t *dest, wchar_t *src);

#endif