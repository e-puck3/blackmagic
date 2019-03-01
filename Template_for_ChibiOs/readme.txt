The modifications made to the Blackmagic firmware let people use it as a submodule for their project using ChibiOS.
In order to use it, you need to :

1) Add these lines somewhere in the makefile in the same manner you need to do with components of ChibiOS. The path should link to the blackmagic folder (the root of the repository) and is referenced from your makefile

BLACKMAGIC = path_to_blackmagic_repo
include $(BLACKMAGIC)/src/platforms/stm32-ChibiOS/Blackmagic_ChibiOS.mk

2) Add $(ALLDEFS) to the UDEFS definition in your makefile

3) Copy the platform.h, platform.c and platform_commands.h files from the template folder, place them where you want in your project and modify what you need inside (mainly the pinout to use). Don't forget to include them in your makefile. platform_commands.h is used to add custom commands to GDB if you want.

4) Use the usbcfg.c/.h files present in the template to configure the USB. They init one or two serial port depending on the config you choose in the usbcfg.h file. You can also use your own usbcfg files but then you need to copy some defines and functions from the usbcfg files from the template folder in order to compile. GDB will use the first USB interface declared.

5) It is possible to implement a second interface to use with GDB. For example the programmer of the e-puck2 robot uses the uart as secon interface for GDB. Since this UART is connected to the bluetooth, it means we can debug the robot by bluetooth or by USB. 