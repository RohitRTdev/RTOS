#ifndef _BASIC_PRINT_H_
#define _BASIC_PRINT_H_

//This module is replaced by a more powerful text mode print functionality once appropriate RT video drivers are set up..

//This function is present to provide basic debugging and logging facilities at early stages of kernel setup
void basic_print(char* str, ...);

#endif