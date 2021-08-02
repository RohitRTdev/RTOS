#ifndef _SYS_ERROR_H_
#define _SYS_ERROR_H_

#include <rtos/rtypes.h>

typedef uint64_t SYS_ERROR;

#define RT_ERROR(error_code) (error_code > 0)

#define NO_ERROR 0x00

#define RT_INFO(error_code) if(RT_ERROR(error_code)) return error_code;

//System 
#define INVALID_PARAMETERS 0X20

//PSF
#define INVALID_PSF_FORMAT 0x01

// Physical memory errors
#define PHY_INSUFFICIENT_MEM 0x01
#define NOT_REQUESTED_SIZE 0x02



//CPU
#define NO_SSE 0x01
#define CPU_NOT_SUPPORTED 0x02

void RT_ERROR_REPORT(char *str, SYS_ERROR status);
void report_error(SYS_ERROR error_code);


#endif