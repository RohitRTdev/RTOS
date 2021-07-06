
/*
* This file is included because microsoft compilers call a helper function with this name 
* when there is a single stack allocation within a function which spans more than a page.
* Failure to include this helper will cause an undefined symbol error in case of 
* heavy stack allocations.
*/ 
.file "helper.s"
.global ___chkstk_ms
.text
.align 0x10

___chkstk_ms:
    ret
