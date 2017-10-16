/******************************************************************************
 * @file    LCDController.h
 * @author   Dua Nguyen
 * @brief    This file consist of classes which use to manage content on screen
 *  and the screen is controlled to display three separate menu
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version   1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef _LCDCONTROLLER_H_
#define _LCDCONTROLLER_H_
#include <Adafruit_SSD1306.h>

/* an I2C sub-class that provides a constructed default */
/* Exceptions: 1. LCD i2c pins are not connected
* @TODO checking logic level of i2c pins and show a notification for user by blink led
*/
/* Exceptions: 2. LCD address is not set correctly
* @TODO make sure that user has checked i2c pins. checking LCD address again
* LCD address can be 0x36 or 0x37 . it depend on logic value of SA0 pin on SSD1306 ic
*/
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    }
};
/* Class content lcd display UI
* If this source file built with example, the <mbed.h> and <LCDController.h> library
* must be included
*/
/*
* Example:
* @code
* TODO: updating
* @endcode
* @ingroup module
*/
class LCDController : private Adafruit_SSD1306_I2c
{
public:
    /************************************
    * Method: LCDController::LCDController
    * @brief: LCDController constructor
    * @param i2c an I2CPreInit object for I2C communication
    * @param RST LCD reset pin. default state is not connected
    * @param rawHeight LCD hight value
    * @param rawWidth LCD width value
    * Access: public
    * Returns:
    * Qualifier:
    ***********************************/

    LCDController(I2C &i2c, PinName RST = NC, uint8_t rawHeight = 64, uint8_t rawWidth = 128):
    Adafruit_SSD1306_I2c(i2c, RST, SSD_I2C_ADDRESS, rawHeight, rawWidth)
    {
        pv_volt = 0;
        pv_curr = 0;
        pv_power = 0;
        pv_energy = 0;
        battery_volt = 0;
        battery_curr = 0;
        battery_power = 0;
        battery_energy = 0;
        second = 0;
        minute = 0;
        hour = 0;
    }
    /*display specific logo on LCD*/
    void ShowLogo();
    /*Update PV voltage value to display */
    void SetPVVolt(float value);
    /*Update PV current value to display */
    void SetPVCurr(float value);
    /*Update PV power value to display */
    void SetPVPower(float value);
    /*Update PV energy value to display */
    void SetPVEnergy(float value);
    /*Update battery voltage value to display */
    void SetBattVolt(float value);
    /*Update battery current value to display */
    void SetBattCurr(float value);
    /*Update battery power value to display */
    void SetBattPower(float value);
    /*Update battery energy value to display */
    void SetBattEnergy(float value);
    /*Change content on screen */
    void UpdateScreen(uint8_t screen_index);
    /*Setting timer value*/
    void SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second);

    float GetPVVolt(void);

    float GetPVCurr(void);

    float GetPVPower(void);

    float GetPVEnergy(void);

    float GetBattVolt(void);

    float GetBattCurr(void);

    float GetBattPower(void);

    float GetBattEnergy(void);

    int GetTime(int);
  



private:
 /**********************************
 *@param second
 *@param minute
 *@param hour
 *Second value, minute value, hour value start 0. when pressing button, it starts to increase
 *it's updated continuously to display on screen
 *@param cursor_pos_col Column position array
 *@param cursor_pos_row row position array
 *The screen is divided to 12 separate area
 *so we need 3 column and 4 row position values to locate a specific area
 **************************************/
   float pv_volt;
   float pv_curr;
   float pv_power;
   float pv_energy;
   float battery_volt;
   float battery_curr;
   float battery_power;
   float battery_energy;
   uint8_t second, minute, hour;

   void WriteAtPosition(uint8_t pos, const char* data);

};

#endif /*_LCDCONTROLLER_H_*/
