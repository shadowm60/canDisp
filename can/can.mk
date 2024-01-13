# List of all the board related files.
CANSRC = ${CHIBIOS}/can/rusefi_can.c

# Required include directories
CANINC = ${CHIBIOS}/can

# Shared variables
ALLCSRC += $(CANSRC)
ALLINC  += $(CANINC)
