
# Imported source files and paths for blackmagic

ifndef BLACKMAGIC
	$(error BLACKMAGIC path is not defined)

else


	
INCDIR += 	$(BLACKMAGIC)/src/target/ \
			$(BLACKMAGIC)/src/include/ \
        	$(BLACKMAGIC)/src/platforms/common/ \
        	$(BLACKMAGIC)/src/platforms/ \
        	$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/

CSRC += 	$(BLACKMAGIC)/src/target/adiv5.c    \
			$(BLACKMAGIC)/src/target/adiv5_swdp.c  \
			$(BLACKMAGIC)/src/command.c \
			$(BLACKMAGIC)/src/target/cortexa.c \
			$(BLACKMAGIC)/src/target/cortexm.c \
			$(BLACKMAGIC)/src/exception.c \
			$(BLACKMAGIC)/src/gdb_main.c  \
			$(BLACKMAGIC)/src/gdb_hostio.c  \
			$(BLACKMAGIC)/src/gdb_packet.c  \
			$(BLACKMAGIC)/src/hex_utils.c \
			$(BLACKMAGIC)/src/morse.c   \
			$(BLACKMAGIC)/src/target/swdptap_generic.c \
			$(BLACKMAGIC)/src/target/target.c  \
			$(BLACKMAGIC)/src/target/stm32f4.c \
			$(BLACKMAGIC)/src/platforms/common/timing.c  \
			$(BLACKMAGIC)/src/platforms/common/swdptap.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/gdb.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/timing_stm32.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/gdb_if.c  \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/serialno.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/crc32_chibios.c

endif

