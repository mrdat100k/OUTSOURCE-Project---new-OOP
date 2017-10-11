#ifndef _IOPIN_H_
#define _IOPIN_H_
/*
*  USB pins:
*  USB_DM = PA_11
*  USB_DP = PA_12
*  USB_NOE = PA_13
*  I2C:
*  I2C_SCL = PB_6
*  I2C_SDA = PB_7
*  SPI for SDIO interface:
*  SPI_MOSI = PB_5
*  SPI_MISO = PB_4
*  SPI_SCK = PB_3
*  SPI_CS = PA_11
*/
/*Button Inputs*/
#define SELECT_BUTTON_PIN PB_0
#define SET_BUTTON_PIN PB_1
#define INVERTER_ON_PIN PB_2
/*Digital Output*/
#define INVERTER_ENABLE_PIN PA_1
/*GPIO*/
#define GPIO_0 PA_2
#define GPIO_1 PA_3
#define GPIO_2 PA_4
#define GPIO_3 PA_5
#define GPIO_4 PA_6
#define GPIO_5 PA_7
#define GPIO_6 PA_8
#define GPIO_7 PA_9
#define GPIO_8 PA_10
#define GPIO_9 PC_14
#define GPIO_10 PC_15

#endif /*_IOPIN_H_*/
