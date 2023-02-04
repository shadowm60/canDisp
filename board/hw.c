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
    SPI_CR1_BR_0 | SPI_CR1_BR_1,   /* spi_lld_config_fields */
    0
  };


void initTFTSPI(void) 
{
    palSetPadMode(IOPORT1, 5, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* SCK. */
    palSetPadMode(IOPORT1, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MISO.*/
    palSetPadMode(IOPORT1, 7, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MOSI.*/
    //palSetPadMode(IOPORT1, 4, PAL_MODE_OUTPUT_PUSHPULL);
    //palSetPad(IOPORT1, 4);
    spiStart(&SPID1, &ls_spicfg); 

    //LED on
    palClearPad(GPIOB, 1U);
}

void tft_spi_csh(void)
{
  //HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
  //spiUnselect(&SPID1);                  /* Slave Select assertion.          */
  palSetPad(GPIOB,0U);
  //spiUnselectI(&SPID1);
}

void tft_spi_csl(void)
{
  //HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
  //spiSelect(&SPID1);                /* Slave Select de-assertion.       */
  palClearPad(GPIOB,0U);
  //spiSelectI(&SPID1);
}

void tft_reset(void)
{
    //HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET);
    //HAL_Delay(5);
    palClearPad(ST7735_RES_GPIO_Port, ST7735_RES_Pin);
    chThdSleepMilliseconds(100);
    palSetPad(ST7735_RES_GPIO_Port, ST7735_RES_Pin);
    chThdSleepMilliseconds(1);
    //HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_SET);
}
void tft_spi_xfer_byte(unsigned char *data, unsigned char len)
{
  //static uint8_t txbuf[64];
  //static uint8_t rxbuf[64];
  //for (unsigned char i=0; i< len; i++) {
  //  txbuf[i] = *data;
  //  data++;
 // }
  spiStartSend(&SPID1, len, data);
  chThdSleepMilliseconds(10);
  //spiExchange(&SPID1,len,txbuf, rxbuf); 
  //(void)rxbuf;
}

void tft_setData(void) 
{
    //HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
    palSetPad(ST7735_DC_GPIO_Port, ST7735_DC_Pin);
    chThdSleepMilliseconds(1);
}

void tft_setCmd(void)
{
    //HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);
    palClearPad(ST7735_DC_GPIO_Port, ST7735_DC_Pin);
    chThdSleepMilliseconds(1);
}

void initLED(void)
{

}

void setLED(void)
{
    //palSetPad(GPIO_LED, GPIOPin_LED);
}

void clrLED(void)
{
   // palClearPad(GPIO_LED, GPIOPin_LED);
}