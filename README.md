Black Magic Probe
=================

This repository is a fork of the BlackMagic [GDB server](https://github.com/blacksphere/blackmagic).
It contains some modifications in order to use it as a submodule for a ChibiOS project.

More info in the dedicated [readme.md](Template_for_ChibiOs/readme.md)

Note : Jtag support has been disabled.
Note 2 : For now, it only works with systems having a MCU frequency around 72MHz-96MHz because the SWD communication implementation is dependant on the MCU frequency.
