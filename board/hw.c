#include "hal.h"
#include "hw.h"
#include "ch.h"

static const SPIConfig ls_spicfg = {
#if (SPI_SUPPORTS_CIRCULAR == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief   Enables the circular buffer mode.
   */
  FALSE, /*                      circular; */
#endif
#if (SPI_SUPPORTS_SLAVE_MODE == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief   Enables the slave mode.
   */
  FALSE, /*                      slave; */
#endif  
    NULL,       /* data_cb; */
    NULL,       /* error_cb; */

    GPIOA,      /* ssport */
    4U,         /* sspad */
    SPI_CR1_BR_0 ,/*| SPI_CR1_BR_1, */  /* spi_lld_config_fields */ //-> 5Mhz
    0
  };


void initTFTSPI(void) 
{
    palSetPadMode(PORT_SPI1_SCK,  PIN_SPI1_SCK,  PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* SCK. */
    palSetPadMode(PORT_SPI1_MISO, PIN_SPI1_MISO, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MISO.*/
    palSetPadMode(PORT_SPI1_MOSI, PIN_SPI1_MOSI, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MOSI.*/
    palSetPadMode(PORT_SPI1_CS,   PIN_SPI1_CS,   PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(ST7735_DC_GPIO_Port,  ST7735_DC_Pin,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(ST7735_RES_GPIO_Port, ST7735_RES_Pin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(ST7735_RES_GPIO_Port, ST7735_RES_Pin);
    
    spiStart(&SPID1, &ls_spicfg); 
}

void tft_spi_csh(void)
{
  //palSetPad(ST7735_CS_GPIO_Port,ST7735_CS_Pin);
  spiUnselect(&SPID1);
}

void tft_spi_csl(void)
{
  //palClearPad(ST7735_CS_GPIO_Port,ST7735_CS_Pin);
  spiSelect(&SPID1);
}

void tft_reset(void)
{
    palClearPad(ST7735_RES_GPIO_Port, ST7735_RES_Pin);
    chThdSleepMilliseconds(50);
    palSetPad(ST7735_RES_GPIO_Port, ST7735_RES_Pin);
    chThdSleepMilliseconds(1);
}
void tft_spi_xfer_byte(unsigned char *data, unsigned char len)
{
  spiStartSend(&SPID1, len, data);
  chThdSleepMicroseconds(1);
}

void tft_spiSend(const void *txbuf, size_t n)
{
  spiStartSend(&SPID1, n, txbuf);
  chThdSleepMicroseconds(1);  
}

void tft_setData(void) 
{
    palSetPad(ST7735_DC_GPIO_Port, ST7735_DC_Pin);
    chThdSleepMicroseconds(1);
}

void tft_setCmd(void)
{
    palClearPad(ST7735_DC_GPIO_Port, ST7735_DC_Pin);
    chThdSleepMicroseconds(1);
}

void tft_Led(uint8_t val)
{
  if (val == LED_FULL) {

    palSetPadMode(ST7735_LED_PORT, ST7735_LED_Pin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(ST7735_LED_PORT, ST7735_LED_Pin);

  } else if (val == LED_OFF){

    palSetPadMode(ST7735_LED_PORT, ST7735_LED_Pin, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(ST7735_LED_PORT, ST7735_LED_Pin);

  } else {

  }

}

void initLED(void)
{

}

void setLED(void)
{
    palSetPad(GPIO_LED, GPIOPin_LED);
}

void clrLED(void)
{
   palClearPad(GPIO_LED, GPIOPin_LED);
}

void toggleLED(void)
{
  palTogglePad(GPIO_LED, GPIOPin_LED);
}