#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "hw.h"

#include "chprintf.h"

#include "usbcfg.h"

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
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  /*  */
  ST7735_Init();
  tft_Led(LED_FULL);
  vData.rpm = 0;
  vData.afr = 1470;

  //ST7735_FillScreenFast(ST7735_BLACK);

  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

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