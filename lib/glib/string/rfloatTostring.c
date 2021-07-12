#include <glib/rstrings.h>

void rfloatTostring(double value, char *str, u8 precision) 
{
    char new_str[MAXCHARCOUNT] = "";
    if(value < 0)
    {
        rstrcpy(new_str, "-");
        value = -1 * value;
    }
    u64 int_value = (u64)value; //Initial integer extraction
    
    
    rtostring(int_value, str);
    
    rstrcat(new_str, str);

    rstrcat(new_str, ".");
    //Extract fractional digits one by one until we obtain precision digits

    value = value - int_value;
    char ch[2];
    while(precision > 0)
    {
        value *= 10;
        int_value = (u64)value;
        rtostring(int_value, ch);
        rstrcat(new_str, ch);
        value = value - int_value;
        precision--;
    }
    rstrcpy(str, new_str);
}