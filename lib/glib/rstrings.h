#ifndef _R_STRINGS_H_
#define _R_STRINGS_H_

#include "glib-types.h"

u64 rstrlen(char *str);
i64 rstrcmp(char *dest, char *src);
void rstrcpy(char *dest, char *src);
void rstrcat(char *dest, char *src);

void reverse_str(char *str);
void rtostring(u64 value, char *str);
void rfloatTostring(double value, char *str, u8 precision);
i8 rtoint(char ch);
bool risdigit(char ch);



u64 wrstrlen(wchar *str);
i64 wrstrcmp(wchar *dest, wchar *src);
void wrstrcpy(wchar *dest, wchar *src);
void wrstrcat(wchar *dest, wchar *src);

#endif