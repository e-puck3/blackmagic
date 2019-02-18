The modifications made to the Blackmagic firmware let people use it as a submodule for their project using ChibiOS.
In order to use it, you need to :

1) Add these lines somewhere in the makefile in the same manner you need to do with components of ChibiOS. The path should link to the blackmagic folder (the root of the repository) and is referenced from your makefile

BLACKMAGIC = path_to_blackmagic_repo
include $(BLACKMAGIC)/src/platforms/stm32-ChibiOS/Blackmagic_ChibiOS.mk

2) Add $(ALLDEFS) to the UDEFS definition in your makefile

3) Copy the platform.h file from the template folder, place it where you want in your project and modify what you need inside (mainly the pinout to use). If you put it in a specific folder, do not forget to include this folder in the compilation.

4) Use the usbcfg.c/.h files present in the template to configure the USB. They init two serial port so the microcontroler used should have at least 5 endpoints. You can also use your own usbcfg files but then you need to copy some defines and functions from the usbcfg files in the template folder in order to compile. 