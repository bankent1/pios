# pios
Toy OS for raspberry pi to work more with ARM architecture. Not sure if this project will ever finish, it is just a hobby project. Feel free to poke around the code and try and get it to run on your hardware.

## Requirements
- arm gcc [cross compiler](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) (make sure to update versions.mk with your version of gcc)
- [qemu](https://www.qemu.org/)
- linux (not tested on mac)
- gnu make
- Raspberry PI (preferably model 2, but 3 should work)

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
