#ifndef _REFI_STAT_H_
#define _REFI_STAT_H_

#include "refidefs.h"
//All error codes have negative values

//For more info on error codes, check Appendix D of UEFI 2.7 specification

#define EFIWARN(a)                            (a)
#define EFI_ERROR(a)              (((INTN)a) < 0)
#define stat_set(a)               ((a) | 0x8000000000000000ULL)  //Set a status code

//Simple macro to test the error code sign
#define stat_check(status) status & ~0x8000000000000000ULL //Macro to clear high bit(Status codes have high bit set by default)



#define EFI_SUCCESS                              0
#define EFI_LOAD_ERROR                  stat_set(1)
#define EFI_INVALID_PARAMETER           stat_set(2)
#define EFI_UNSUPPORTED                 stat_set(3)
#define EFI_BAD_BUFFER_SIZE             stat_set(4)
#define EFI_BUFFER_TOO_SMALL            stat_set(5)
#define EFI_NOT_READY                   stat_set(6)
#define EFI_DEVICE_ERROR                stat_set(7)
#define EFI_WRITE_PROTECTED             stat_set(8)
#define EFI_OUT_OF_RESOURCES            stat_set(9)
#define EFI_VOLUME_CORRUPTED            stat_set(10)
#define EFI_VOLUME_FULL                 stat_set(11)
#define EFI_NO_MEDIA                    stat_set(12)
#define EFI_MEDIA_CHANGED               stat_set(13)
#define EFI_NOT_FOUND                   stat_set(14)
#define EFI_ACCESS_DENIED               stat_set(15)
#define EFI_NO_RESPONSE                 stat_set(16)
#define EFI_NO_MAPPING                  stat_set(17)
#define EFI_TIMEOUT                     stat_set(18)
#define EFI_NOT_STARTED                 stat_set(19)
#define EFI_ALREADY_STARTED             stat_set(20)
#define EFI_ABORTED                     stat_set(21)
#define EFI_ICMP_ERROR                  stat_set(22)
#define EFI_TFTP_ERROR                  stat_set(23)
#define EFI_PROTOCOL_ERROR              stat_set(24)
#define EFI_INCOMPATIBLE_VERSION        stat_set(25)
#define EFI_SECURITY_VIOLATION          stat_set(26)
#define EFI_CRC_ERROR                   stat_set(27)
#define EFI_END_OF_MEDIA                stat_set(28)
#define EFI_END_OF_FILE                 stat_set(31)
#define EFI_INVALID_LANGUAGE            stat_set(32)
#define EFI_COMPROMISED_DATA            stat_set(33)

#define EFI_WARN_UNKOWN_GLYPH           EFIWARN(1)
#define EFI_WARN_DELETE_FAILURE         EFIWARN(2)
#define EFI_WARN_WRITE_FAILURE          EFIWARN(3)


/* RTOS bootloader defined errors */
#define KERNEL_LOAD_ERROR                stat_set(50)
#define FONT_NOT_SUPPORTED               stat_set(51)
#define UNSUPPORTED_EXECUTABLE_FORMAT    stat_set(52)
#define ACPI_ERROR                       stat_set(53)
#endif