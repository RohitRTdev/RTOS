#include <refilib.h>
#include <stdarg.h>

static void conv64tostr(UINT64 value, CHAR16* outstr)
{
    UINT64 sample = value;
    if(sample == 0)
    { 
        *(outstr) = (CHAR16)'0';
        *(outstr+1) = (CHAR16)'\0';}
    else
    {
        UINT64 i = 0,j = 0;
        CHAR16 outrev[20];
        while(sample > 0)
        {
            *(outrev+i) = (CHAR16)(sample % 10 + 48);
            sample /= 10; 
            i++;

        }
        while(i>0)
        {
            i--;
            *(outstr+j) = *(outrev+i);
            j++;
        }
        *(outstr + j) = (CHAR16)'\0';}


}

static UINT64 print_parser(CHAR16 *str, UINT64 lastlocation, UINT8 *type)
{
    UINT8 flag = 0x00;
    UINT64 i = lastlocation + 1;
    
    while(!(str[i] == L'%'))
    {
        if(str[i] == L'\0')
            return 0XFFFFFFFF;
        i++;
    }
    if(str[i+1] == L'd')
        flag = 0x01;
    else if(str[i+1] == L's')
    {
        flag = 0x02;
    }
    else 
         i = print_parser(str, i, &flag);
    
    *type = flag;
    return i;
}
static EFI_STATUS inline print_string(CHAR16 *str)
{
    EFI_STATUS status;
    status = ST->ConOut->OutputString(ST->ConOut, str);
    return status;
}

EFI_STATUS printEFI(CHAR16* str, ...)
{
    EFI_STATUS status;
    CHAR16 new_str[100];
    CHAR16 tmp_str[100];
    UINT64 counterold = 0, counternew = 0, countertmp = 0;
    UINT64 location = 0, sub; 
    CHAR16 *str_hold;
    UINT8 type = 0x00;
    UINT64 last_location = location - 1;
    va_list args;
    va_start(args, 10);

    while(location != 0xFFFFFFFF)
    {
        counternew = 0; 
        location = print_parser(str, last_location, &type);
        if(location == 0XFFFFFFFF)
        {
            while(str[counterold] != L'\0')
            {
                tmp_str[countertmp++] = str[counterold++];
            }
            continue;
        }
        while(counterold < location)
        {
            tmp_str[countertmp++] = str[counterold++];
        }
        if(type == 0x01)
        {
            sub = va_arg(args, UINT64);
            conv64tostr(sub, new_str);
            while(new_str[counternew] != L'\0')
            {
                tmp_str[countertmp++] = new_str[counternew++];  
            }
            
           
        }
        else if(type == 0x02)
        {
            str_hold = va_arg(args, CHAR16*);
            while(str_hold[counternew] != L'\0')
            {
                tmp_str[countertmp++] = str_hold[counternew++];
            }
        }
        counterold += 2;
        last_location = location;
    }
     
    va_end(args);
    tmp_str[countertmp] = L'\0';
    status = print_string(tmp_str);
    return status;    
}