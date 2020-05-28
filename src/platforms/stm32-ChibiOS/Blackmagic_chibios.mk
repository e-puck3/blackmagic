
# Imported source files and paths for blackmagic

NO_JTAG = 1

ALLDEFS +=	-DUSE_CHIBIOS -DPC_HOSTED=0

ifdef NO_JTAG
	ALLDEFS +=	-DPLATFORM_HAS_NO_JTAG
endif

	
ALLINC += 	$(BLACKMAGIC)/src/target/ \
			$(BLACKMAGIC)/src/include/ \
        	$(BLACKMAGIC)/src/platforms/common/ \
        	$(BLACKMAGIC)/src/platforms/ \
        	$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/

ALLCSRC += 	$(BLACKMAGIC)/src/target/adiv5.c    \
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
			$(BLACKMAGIC)/src/remote.c \
			$(BLACKMAGIC)/src/target/target.c  \
			$(BLACKMAGIC)/src/target/stm32f4.c \
			$(BLACKMAGIC)/src/platforms/common/timing.c  \
			$(BLACKMAGIC)/src/platforms/common/swdptap.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/gdb.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/timing_stm32.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/gdb_if.c  \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/serialno.c \
			$(BLACKMAGIC)/src/platforms/stm32-ChibiOS/crc32_chibios.c \
			$(BLACKMAGIC)/src/target/stm32f1.c	\
			$(BLACKMAGIC)/src/target/stm32l0.c	\
			$(BLACKMAGIC)/src/target/stm32l4.c	\
			$(BLACKMAGIC)/src/target/stm32h7.c \
			$(BLACKMAGIC)/src/target/msp432.c \
			$(BLACKMAGIC)/src/target/lpc17xx.c \
			$(BLACKMAGIC)/src/target/lpc_common.c	\
			$(BLACKMAGIC)/src/target/lpc11xx.c	\
			$(BLACKMAGIC)/src/target/lpc15xx.c	\
			$(BLACKMAGIC)/src/target/lpc43xx.c	\
			$(BLACKMAGIC)/src/target/sam3x.c		\
			$(BLACKMAGIC)/src/target/sam4l.c	\
			$(BLACKMAGIC)/src/target/nrf51.c		\
			$(BLACKMAGIC)/src/target/samd.c		\
			$(BLACKMAGIC)/src/target/lmi.c		\
			$(BLACKMAGIC)/src/target/kinetis.c	\
			$(BLACKMAGIC)/src/target/efm32.c \
			$(BLACKMAGIC)/src/target/nxpke04.c \
			$(BLACKMAGIC)/src/target/samx5x.c

ifndef NO_JTAG
	ALLCSRC +=	$(BLACKMAGIC)/src/target/adiv5_jtagdp.c \
				$(BLACKMAGIC)/src/target/jtag_scan.c	\
				$(BLACKMAGIC)/src/platforms/jtagtap.c	\
				$(BLACKMAGIC)/src/target/jtagtap_generic.c
endif

# endif

