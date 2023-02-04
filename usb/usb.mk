# List of all the board related files.
USBSRC = ${CHIBIOS}/usb/usbcfg.c

# Required include directories
USBINC = ${CHIBIOS}/usb

# Shared variables
ALLCSRC += $(USBSRC)
ALLINC  += $(USBINC)