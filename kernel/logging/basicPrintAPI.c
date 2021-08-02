#include <rtos/rtypes.h>
#include <logging/logger.h>
#include <stdarg.h>
#include <glib/rstrings.h>

#pragma GCC diagnostic ignored "-Wvarargs"

static uint64_t basic_print_parser(char *str, uint64_t lastlocation, uint8_t *type, uint64_t length, uint8_t *precision)
{
    uint8_t flag = 0x00;
    uint64_t i = lastlocation + 1;
    int8_t digittest;
    uint8_t accuracy = 0;
  
    while(!(str[i] == '%'))
    {
        if(str[i] == '\0')
            return 0XFFFFFFFF;
        i++;
    }
    if(str[i+1] == 'd')
    {
        flag = 0x01;
    }
    else if(str[i+1] == 's')
    {
        flag = 0x02;
    }
    else if(str[i+1] == 'i')
    {
        flag = 0x03;
    }
    else if((length - (i + 1)) >= 2)
    {
        //Max three digits precision
        if(str[i + 2] == 'f') 
        {

            digittest = rtoint(str[i + 1]);
            if(digittest == -1)
                goto special_case;
            accuracy = digittest;
            flag = 0x04;
        }
        else if(str[i + 3] == 'f' && ((length - (i + 1)) >= 3))
        {

            uint8_t fi = i + 1;
            while(fi < i + 3)
            {
                digittest = rtoint(str[fi]);
                if(digittest == -1)
                    goto special_case;
                accuracy = accuracy*10 + digittest;
                fi++;

            }
            flag = 0x04;
        }
        else if(str[i + 4] == 'f' && ((length - (i + 1)) >= 4))
        {

            uint8_t fi = i + 1;
            while(fi < i + 4)
            {
                digittest = rtoint(str[fi]);
                if(digittest == -1)
                    goto special_case;
                accuracy = accuracy*10 + digittest;
                fi++;
            }
            flag = 0x04;
        }
        else 
            goto special_case;
        
    }
    else
    {
        special_case:
        i = basic_print_parser(str, i, &flag, length, &accuracy);
    }
    
    *precision = accuracy;
    *type = flag;
    return i;
}
void basic_print(char* str, ...)
{
    char new_str[MAXCHARCOUNT];
    char tmp_str[MAXCHARCOUNT];
    char negative_holder[MAXCHARCOUNT] = "-";
    uint8_t precision = 0;
    uint64_t length = rstrlen(str);
    uint64_t counterold = 0, counternew = 0, countertmp = 0;
    uint64_t location = 0, sub_u;
    int64_t sub_i; 
    char *str_hold;
    double double_hold;
    uint8_t type = 0x00;
    uint64_t last_location = location - 1;
    va_list args;
    const uint8_t num_args = 10;
    va_start(args, num_args);

    while(location != 0xFFFFFFFF)
    {
        counternew = 0; 
        location = basic_print_parser(str, last_location, &type, length, &precision);
        if(location == 0XFFFFFFFF)
        {
            while(str[counterold] != '\0')
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
            sub_u = va_arg(args, uint64_t);
            rtostring(sub_u, new_str);
            while(new_str[counternew] != '\0')
            {
                tmp_str[countertmp++] = new_str[counternew++];  
            }
            
           
        }
        else if(type == 0x02)
        {
            str_hold = va_arg(args, char*);
            while(str_hold[counternew] != '\0')
            {
                tmp_str[countertmp++] = str_hold[counternew++];
            }
        }
        else if(type == 0x03)
        {
            sub_i = va_arg(args, int64_t);
            if(sub_i < 0)
            {
                sub_i = -sub_i;
                rtostring(sub_i, new_str);

                rstrcat(negative_holder, new_str);
                
                rstrcpy(new_str, negative_holder);
                rstrcpy(negative_holder, "-");
            }
            else 
                rtostring(sub_i, new_str);
            while(new_str[counternew] != '\0')
            {
                tmp_str[countertmp++] = new_str[counternew++];
            }
        }
        else if(type == 0x04)
        {
            double_hold = va_arg(args, double);
            rfloatTostring(double_hold, new_str, precision);
            while(new_str[counternew] != '\0')
            {
                tmp_str[countertmp++] = new_str[counternew++];
            }
            if(precision < 10)
                counterold++;
            else if(precision < 100)
                counterold += 2;
            else if(precision < 256)
                counterold += 3;
            precision = 0;
        }
        counterold += 2;
        last_location = location;
    }
     
    va_end(args);
    tmp_str[countertmp] = '\0';
    basic_print_str(tmp_str);    
}
