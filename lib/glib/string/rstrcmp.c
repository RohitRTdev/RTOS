#include <glib/rstrings.h>

int64_t rstrcmp(char *str1, char *str2)
{
    int64_t length = 0, str1Length = rstrlen(str1), str2Length = rstrlen(str2);
    while(str1[length] == str2[length] && !(str1[length] == '\0' ||str2[length] == '\0'))
    {
        length++;
    }
    if(str1Length == str2Length && length == str1Length)
        return 0;
    else if(str1Length > str2Length && length == str2Length)
        return 1;
    else if(str1Length < str2Length && length == str1Length)
        return -1;
    else if(str1[length] > str2[length])
        return 1;

    return -1;   

}