This project is a brilliant example of my procrastination, and how I invited it by assigning myself a pretty difficult goal. Don't be like me guys.
Make doable goals for yourself and you will feel like doing it. 
Thank you and have a nice day.. 
Rohit. Signing off...


# RTOS
RTOS is X64 based OS that is UEFI compliant.

## Description
The OS is at a very early stage and only sports basic services. RTOS follows the windows philosophy of **everything is an object**.

**Services**
* UEFI bootloader
* Basic print service 
* Extremely basic graphics( without graphics card and lot of work to set up)
* A physical memory manager

## Build

* Download mingw

* To build the OS, simply clone the directory and execute 
>>make build [PRETTY_PRINT=DISABLE] #Anything within [  ] is optional and the option is self explanatory

This will create output files RT_core.rm in kernel directory and BOOTx64.EFI in boot directory.
Now create a disk image with EFI partition containing the following hierarchy.

Each of the below is a folder with a file at the end.    
EFI--> BOOT --> BOOTx64.EFI  
Modules--> RT_core.rm
Fonts--> *.psf(font files present in resources directory)  

## Testing 
Testing can be done by burning the image file to a flash drive and running it on real machine by choosing to boot through the flash drive in BIOS setup.
Make sure that you have disabled secure boot in the BIOS setup or the OS won't load.

The image file can also be loaded in qemu and run, but make sure to use OVMF.fd as qemu uses the old BIOS bootload mechanism and RTOS only supports the newer UEFI bootloading mechanism.


