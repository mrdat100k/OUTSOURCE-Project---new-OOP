/*!
 * \file var.h
 * \summary file khai báo các driver của phần cứng, các biến phần cứng toàn cục,
 * và các biến trạng thái của hệ thống.
 *
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
Adafruit_SSD1306_I2c g_lcd_object(g_I2C_object, NC);
INA219 g_battery_measure_object(I2C_SDA, I2C_SCL, INA219_measure_battery_addr);
INA219 g_pv_measure_object(I2C_SDA, I2C_SCL, INA219_measure_pv_addr);
InterruptIn g_set_button(SET_BUTTON_PIN);
InterruptIn g_select_button(SELECT_BUTTON_PIN);
InterruptIn g_inverter_on(INVERTER_ON_PIN);
RTC_Timer g_rtc_timer;
uint8_t g_menu_index;
Timeout g_timeout;
#endif /*_VAR_H_*/
