#include <rstrings.h>

int64_t rstrcmp(char *str1, char *str2)
{
    uint64_t length = 0, str1Length = crstrlen(str1), str2Length = crstrlen(str2);
    while(str1[length] == str2[length] && !(str1[length] == RTEXT('\0') ||str2[length] == RTEXT('\0')))
    {
        length++;
    }
    if(str1Length == str2Length)
        if(length == str1Length)
            return 0;
    else if(str1Length > str2Length && length == str2Length)
        return 1;
    else if(str1Length < str2Length && length == str1Length)
        return -1;
    else if(str1[length] > str2[length])
        return 1;
    else 
        return -1;    

}