#include <error/syserror.h>
#include <rtypes.h>
#include <logging/basic_print.h>

static SYS_ERROR rerrno;

void report_error(SYS_ERROR error_code)
{
    rerrno = error_code;
}

void RT_ERROR_REPORT(char *str, SYS_ERROR status)
{
    if(RT_ERROR(status))
    {
        rerrno = status;
        basic_print("%s\n\r", str);
        basic_print("Error code:%d\r\n", status);
        basic_print("Cannot continue execution\r\n");
        while(1){}
    }
}
