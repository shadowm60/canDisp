#ifndef _HW_H_
#define _HW_H_

/******************************************************/
/* HW connection used:                                */
/* UART:                                              */
/*     TX1 - PA9                                      */
/*     RX1 - PA10                                     */
/* CAN:                                               */
/*     CANRX - PB8                                    */
/*     CANTX - PB9                                    */
/* USB:                                               */
/*     USB-  - PA11                                   */
/*     USB+  - PA12                                   */
/* SDCARD:                                            */
/*     NSS2  - PB12                                   */
/*     SCK2  - PB13                                   */
/*     MISO2 - PB14                                   */
/*     MOSI2 - PB15                                   */
/* LCD:                                               */
/*     RST -  PB11                                    */
/*     CS  -  PA4                                     */
/*     RS  - D/C - PB10                               */
/*     SDA - MOSI1 - PA7                              */
/*     SCL - SCK1 - PA5                               */
/*     LED - PB1 - T3C4                               */
/* LED:                                               */
/*     PC13                                           */
/******************************************************/

/* GPIO number definition */
#define GPIOPin_LED     13U
#define GPIO_LED        GPIOC

/* 1.44" TFT */
#define ST7735_RES_Pin       11U
#define ST7735_RES_GPIO_Port GPIOB
#define ST7735_CS_Pin        4U
#define ST7735_CS_GPIO_Port  GPIOA
#define ST7735_DC_Pin        10U
#define ST7735_DC_GPIO_Port  GPIOB

#define PORT_SPI1_SCK       GPIOA
#define PORT_SPI1_MISO      GPIOA
#define PORT_SPI1_MOSI      GPIOA
#define PORT_SPI1_CS        GPIOA

#define PIN_SPI1_SCK        5U
#define PIN_SPI1_MISO       6U
#define PIN_SPI1_MOSI       7U
#define PIN_SPI1_CS         4U

void initTFTSPI(void);
void tft_spi_csh(void);
void tft_spi_csl(void);
void tft_reset(void);
void tft_spi_xfer_byte(unsigned char *data, unsigned char len);
void tft_setData(void);
void tft_setCmd(void);



/* LED */

void initLED(void);
void setLED(void);
void clrLED(void);


#endif