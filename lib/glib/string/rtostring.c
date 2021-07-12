#include <glib/rstrings.h>

void rtostring(u64 value, char *outstr)
{
    u64 sample = value;
    if(sample == 0)
    { 
        outstr[0] = '0';
        outstr[1] = '\0';}
    else
    {
        u64 i = 0,j = 0;
        char outrev[MAXCHARCOUNT];
        while(sample > 0)
        {
            outrev[i] = sample % 10 + 48;
            sample /= 10; 
            i++;

        }
        while(i>0)
        {
            i--;
            outstr[j] = outrev[i];
            j++;
        }
        outstr[j] = '\0';}

}