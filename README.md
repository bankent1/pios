# Pios
Toy OS for raspberry pi to work more with ARM architecture. Not sure if this project will ever finish, it is just a hobby project. Feel free to poke around the code and try and get it to run on your hardware.  

## Helpful Resources
If you are interested in making your own arm-based OS, these sites really helped me out:  
- [Building an OS for the Raspberry PI](https://jsandler18.github.io/)  
- [OSDev Wiki](https://wiki.osdev.org/Main_Page)  

**Manuals**  
- [Arm Reference Manual](https://www.scss.tcd.ie/~waldroj/3d1/arm_arm.pdf)  
- [Cortex-a7 Manual](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0464d/DDI0464D_cortex_a7_mpcore_r0p3_trm.pdf)  
- [Cortex-a53 Manual](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0500d/DDI0500D_cortex_a53_r0p2_trm.pdf)  
- [Raspberry PI Peripherals Manual](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)  


## Requirements
- [arm gcc cross compiler](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) (make sure to update versions.mk with your version of gcc)
- [qemu](https://www.qemu.org/)
- linux (not tested on mac)
- gnu make
- Raspberry PI (preferably model 2, but 3 should work)

## Setting up the Project
- After downloading the gcc cross compiler, move the directory (named `gcc-arm-none-eabi-X-XXXX-XX-update`) to the root of the project.
- Update the `GCC_VERSION` var in the `versions.mk` file with the version you downloaded. It should be in the form `X-XXXX-XX`.
- Make sure that your qemu versions supports `qemu-system-arm` and `raspi2` machine as this is what is used as virtualized hardware

## Build
```make build```  

## Run (QEMU)
```make run```  

## Run (Hardware)
```make VIRTUALIZED=0```  
This generates a img file in `build/` directory. Copy this over to your SD card to install onto the PI.

## Tests
```make tests```  
or  
```cd test; make run```  

Tests are located in `<subdir>/test/`  
The root `test/` directory will contain the makefile needed to auto build all of the tests written. However, running the first command from root will auto build all tests and start qemu.
To build an img for hardware using the test files, use  
```cd test; make build```
