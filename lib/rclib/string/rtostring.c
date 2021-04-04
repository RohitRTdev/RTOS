#include <rstrings.h>

void rtostring(uint64_t value, char *outstr)
{
    uint64_t sample = value;
    if(sample == 0)
    { 
        outstr[0] = '0';
        outstr[1] = '\0';}
    else
    {
        uint64_t i = 0,j = 0;
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