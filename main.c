#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "hw.h"

#include "chprintf.h"
#ifdef USB_DEBUG
#include "usbcfg.h"
#endif
#include "st7735.h"
#include "fonts.h"

void test_tft(void);
void screen1(void);

typedef struct {
  uint16_t rpm;
  uint16_t afr; //14.70 = 1470
}tstVehData;


tstVehData vData;


/*
 * Internal loopback mode, 500KBaud, automatic wakeup, automatic recover
 * from abort mode.
 * See section 22.7.7 on the STM32 reference manual.
 */

static const CANConfig cancfg = {
  CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
  CAN_BTR_LBKM | CAN_BTR_SJW(0) | CAN_BTR_TS2(1) |
  CAN_BTR_TS1(8) | CAN_BTR_BRP(6)
};

/*
 * Alive indicator led.
 */
static THD_WORKING_AREA(waThread1, 256);
static THD_FUNCTION(Thread1, arg) {

  
  (void)arg;
  chRegSetThreadName("blinker");
  setLED();

  ST7735_FillScreen(ST7735_BLACK);
  
  while (true) {
    //test_tft();
    screen1();
    toggleLED();
    chThdSleepMilliseconds(200);

  }
}


static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
    (void)arg;
    chRegSetThreadName("dUpdater");

    while(true) {
      chThdSleepMilliseconds(500);
      vData.rpm += 100;
      if (vData.rpm > 7000) { vData.rpm = 800; }

      vData.afr += 10;
      if (vData.afr > 1700) { vData.afr = 1310; }
    }
}



/*
 * Receiver thread.
 */
static THD_WORKING_AREA(can_rx_wa, 256);
static THD_FUNCTION(can_rx, p) {
  event_listener_t el;
  CANRxFrame rxmsg;

  (void)p;
  chRegSetThreadName("receiver");
  chEvtRegister(&CAND1.rxfull_event, &el, 0);
  while (true) {
    if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0)
      continue;
    while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
      /* Process message.*/
      //palTogglePad(IOPORT3, GPIOC_LED);
    }
  }
  chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
static THD_WORKING_AREA(can_tx_wa, 256);
static THD_FUNCTION(can_tx, p) {
  CANTxFrame txmsg;

  (void)p;
  chRegSetThreadName("transmitter");
  txmsg.IDE = CAN_IDE_EXT;
  txmsg.EID = 0x01234567;
  txmsg.RTR = CAN_RTR_DATA;
  txmsg.DLC = 8;
  txmsg.data32[0] = 0x55AA55AA;
  txmsg.data32[1] = 0x00FF00FF;

  while (true) {
    canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, TIME_MS2I(100));
    chThdSleepMilliseconds(500);
  }
}



/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is avctive.
   */
  halInit();
  chSysInit();

  /*
   * Activates the CAN driver 1.
   */
  initCANPins();
  canStart(&CAND1, &cancfg);

#ifdef USB_DEBUG
  /*
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);
#endif

  /*  */
  tft_Led(LED_OFF);
  ST7735_Init();
  ST7735_FillScreen(ST7735_BLACK);
  tft_Led(LED_FULL);
  vData.rpm = 0;
  vData.afr = 1470;

  //ST7735_FillScreenFast(ST7735_BLACK);
#ifdef USB_DEBUG
  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);
#endif
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
  chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
      chThdSleepMilliseconds(300);
      //test_tft();
  }
}

void screen1(void)
{
    //ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
    static char val[20];
    ST7735_WriteString(0, 0, "RPM: ", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    //bzero(val,20);
    //sprintf(val,"%d",vData.rpm);
    ST7735_WriteString(11*5, 0, "850", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(0, 18, "AFR: ", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    //sprintf(val,"%d.%d",(vData.afr / 100),(vData.afr%100));
    //val[5] = '\0';
    ST7735_WriteString(11*5, 18, "14.40", Font_11x18, ST7735_GREEN, ST7735_BLACK);
}