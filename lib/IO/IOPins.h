/******************************************************************************
 * @file    IOPins.h
 * @author   Dua Nguyen
 * @brief   Contains IO Pins map using for the demo
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef LIB_IO_IOPINS_H_
#define LIB_IO_IOPINS_H_
/*
*  USB pins:
*  USB_DM = PA_11
*  USB_DP = PA_12
*  USB_NOE = PA_13
*  I2C:
*  I2C_SCL = PB_6
*  I2C_SDA = PB_7
*/
/*SPI for SDIO interface: */
#define SDIO_MOSI PA_7
#define SDIO_MISO PA_6
#define SDIO_SCK PA_5
#define SDIO_CS PA_4

/*Button Inputs*/
#define SELECT_BUTTON_PIN PB_0
#define SET_BUTTON_PIN PB_1
#define INVERTER_ON_PIN PB_3
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

#endif /*LIB_IO_IOPINS_H_*/
