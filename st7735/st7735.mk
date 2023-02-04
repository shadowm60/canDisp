# List of all the board related files.
TFTSRC = ${CHIBIOS}/st7735/st7735.c \
		 ${CHIBIOS}/st7735/fonts.c

# Required include directories
TFTINC = ${CHIBIOS}/st7735

# Shared variables
ALLCSRC += $(TFTSRC)
ALLINC  += $(TFTINC)