#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "hw.h"

#include "chprintf.h"

#include "usbcfg.h"

#include "st7735.h"
#include "fonts.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

void test_tft(void);


/*
 * Alive indicator led.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  
  (void)arg;
  chRegSetThreadName("blinker");
  setLED();

  ST7735_WriteString(0,0,"HELLO",Font_16x26,ST7735_GREEN,ST7735_BLACK);


  while (true) {
    //clrLED();
    //chThdSleepMilliseconds(300);
    //chThdSleepMilliseconds(700);
    test_tft();
    ST7735_FillScreen(ST7735_BLACK);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_BLUE);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_RED);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_GREEN);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_CYAN);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_MAGENTA);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_YELLOW);
    toggleLED();
    chThdSleepMilliseconds(1000);
    ST7735_FillScreen(ST7735_WHITE);
    toggleLED();
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
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  /*  */
  ST7735_Init();
  tft_Led(LED_FULL);

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

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
      chThdSleepMilliseconds(300);
      //test_tft();
  }
}



void test_tft(void) {
    // Check border
    ST7735_FillScreen(ST7735_BLACK);
    chThdSleepMilliseconds(100);

    for(int x = 0; x < ST7735_WIDTH; x++) {
        ST7735_DrawPixel(x, 0, ST7735_RED);
        ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
    }

    for(int y = 0; y < ST7735_HEIGHT; y++) {
        ST7735_DrawPixel(0, y, ST7735_RED);
        ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
    }

    chThdSleepMilliseconds(100);

    // Check fonts
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
    ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
    chThdSleepMilliseconds(2000);

// Check colors
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_BLUE);
    ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_RED);
    ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_GREEN);
    ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_CYAN);
    ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_MAGENTA);
    ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_YELLOW);
    ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
    chThdSleepMilliseconds(500);

    ST7735_FillScreen(ST7735_WHITE);
    ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
    chThdSleepMilliseconds(500);

}