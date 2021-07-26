#include <glib/rstrings.h>

int64_t wrstrcmp(wchar_t *str1, wchar_t *str2)
{
    uint64_t length = 0, str1Length = wrstrlen(str1) - 1, str2Length = wrstrlen(str2) - 1;
    while(str1[length] == str2[length] && !(str1[length] == L'\0' ||str2[length] == L'\0'))
    {
        length++;
    }
    if(length == str1Length && length == str2Length)
            return 0;
    else if(str1Length > str2Length && length == str2Length + 1)
        return 1;
    else if(str1Length < str2Length && length == str1Length + 1)
        return -1;
    else if(str1[length] > str2[length])
        return 1;
    else 
        return -1;    

}