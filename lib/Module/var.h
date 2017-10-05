/*!
 * \file var.h
 * \summary  
 * Declaring global variables, status variables and drives
 * \author
 *
 * \date October 2017
 *
 *
 */
#ifndef _VAR_H_
#define _VAR_H_
#define INA219_measure_battery_addr 0x40
#define INA219_measure_pv_addr 0x41
#include <Adafruit_SSD1306.h>
#include <INA219.hpp>
#include <IOPins.h>
#include <RTCTimer.h>
/*GLOBAL VARIBLES*/
/* an I2C sub-class that provides a constructed default */
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};
I2CPreInit g_I2C_object(I2C_SDA, I2C_SCL);
/*screen object */
Adafruit_SSD1306_I2c g_lcd_object(g_I2C_object, NC);
/*INA module object*/
INA219 g_battery_measure_object(I2C_SDA, I2C_SCL, INA219_measure_battery_addr);
INA219 g_pv_measure_object(I2C_SDA, I2C_SCL, INA219_measure_pv_addr);
#endif /*_VAR_H_*/
