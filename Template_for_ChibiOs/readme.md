Blackmagic for ChibiOS
======================

Files description
-----------------
Here is a list of the important files contained in **Template_for_ChibiOs** :

- **platform.c** --File containing some platform dependent functions. Depending on the settings made in **platform.h**, two functions have to be filled.
- **platform.h** --File used to make the link between the project's specific settings and the blackmagic part. It is needed to modify it to configure correctly the GPIOs to use for GDB and to enable/disable some functionalities.
- **platform_commands.h** --This file lets the user add custom commands to the GDB command line interface if needed.
- **usbcfg.c** --Contains the USB implementation and functions to create one or two serial ports over USB.
- **usbcfg.h** -Contains the USB settings the user can change if necessary (Device name, Vendor name etc).

Note : It is possible to go take a look at the [e-puck2-programmer](https://github.com/e-puck2/e-puck2-programmer) code to have an example on how to configure and use these files.

Build instructions
------------------
The modifications made to the Blackmagic firmware let people use it as a submodule for their project using ChibiOS.
In order to use it, you need to :

- Add the specific variables below to your makefile before the **CSRC** definition
  - ``BLACKMAGIC`` : Path to the blackmagic folder (relative to the ChibiOS makefile)
  - ``include $(BLACKMAGIC)/src/platforms/stm32-ChibiOS/Blackmagic_ChibiOS.mk``
- Add these variables in your makefile if it's not already the case
	-	``$(ALLCSRC)`` 	to 	``CSRC``
	-	``$(ALLINC)`` 	to 	``INCDIR``
	-	``$(ALLDEFS)`` 	to 	``UDEFS``
- Copy the **platform.h**, **platform.c** and **platform_commands.h** files from the **Template_for_ChibiOs** folder and place them where you want in your project and modify what you need inside (mainly the pinout to use). Don't forget to include them in your makefile. 
- Use the **usbcfg.c/.h** files present in the **Template_for_ChibiOs** folder to configure the USB. They initialize one or two serial ports depending on the config you choose in **usbcfg.h**. You can also use your own usbcfg files but then you need to copy some defines and functions from the **usbcfg.c/.h** files in order to compile. GDB will use **USB_GDB**, which is the first USB interface declared.

Special notes
-------------
- It is possible to implement a second interface to use with GDB. For example the programmer of the e-puck2 robot uses one UART as a second interface for GDB. Since this UART is connected to the bluetooth, it means we can debug the robot by bluetooth or by USB. The second interface is only used when the USB is unconnected.
- Although it is possible to declare two serial ports over USB in **usbcfg.h**, this functionality can only work if the used MCU has enough endpoints. Since each serial port over USB uses 1 IN/OUT endpoint and 1 IN endpoint, it needs a MCU with at least 4 endpoints to work. Otherwise the USB simply doesn't work at all.