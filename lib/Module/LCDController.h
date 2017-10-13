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
#include <logo.h>
/* an I2C sub-class that provides a constructed default */
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
    void  UpdateScreen(uint8_t screen_index);
    /*Setting timer value*/
    void SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second);
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
    /************************************
    * Method: LCDController::ShowLogo
    * Description: Showing a specific logo on screen
    * Access: Public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::ShowLogo()
{
    clearDisplay();
    drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
    display();
}
    /************************************
    * Method: LCDController::SetPVVolt
    * Description: Updating PV voltage value to display
    * Access: public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::SetPVVolt(float value)
{
    pv_volt = value;
}
    /************************************
    * Method: LCDController::SetPVCurr
    * Description: updating PV current value to display
    * Access: public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::SetPVCurr(float value)
{
    pv_curr = value;
}
    /************************************
    * Method: LCDController::SetPVPower
    * Description: Updating PV power value to display
    * Access: Public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::SetPVPower(float value)
{
    pv_power = value;
}
    /************************************
    * Method: LCDController::SetPVEnergy
    * Description: Updating PV energy value to display
    * Access: Public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::SetPVEnergy(float value)
{
    pv_energy = value;
}
    /************************************
    * Method: LCDController::SetBattVolt
    * Description: Updating battery voltage value to display
    * Access: Public
    * Returns:
    * Qualifier:
    *************************************/
void LCDController::SetBattVolt(float value)
{
    battery_volt = value;
}
   /************************************
    * Method: LCDController::SetBattCurr
    * Description: Updating battery current value to display
    * Access: Public
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::SetBattCurr(float value)
{
    battery_curr = value;
}
   /************************************
    * Method: LCDController::SetBattPower
    * Description: Updating battery power value to display
    * Access: Public
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::SetBattPower(float value)
{
    battery_power = value;
}
   /************************************
    * Method: LCDController::SetBattEnergy
    * Description: Updating battery energy value to display
    * Access: Public
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::SetBattEnergy(float value)
{
    battery_energy = value;
}
   /************************************
    * Method: LCDController::SetTime
    * Description: Updating time to display
    * Access: Public
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    hour = _hour;
    minute = _minute;
    second = _second;
}
   /************************************
    * Method: LCDController::UpdateScreen
    * Description: Change menu screen
    * There are 3 different menu screen
    * Before updating a new screen, we need to call clearing display function
    * @para screen_index The variable determine which menu screen is displayed
    * Access: Public
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::UpdateScreen(uint8_t screen_index)
{
    char buff[12]; /*Data buffer*/
    clearDisplay();
    /* Update screen contents */
    switch (screen_index)
    {
        case(0) : {

            WriteAtPosition(0, "MAIN MENU");
            WriteAtPosition(1, "Charge");
            WriteAtPosition(2, "Yes");
            WriteAtPosition(3, "DC");
            WriteAtPosition(4, "Battery");
            sprintf(buff, "%2.1fV ", battery_volt/1000);
            WriteAtPosition(5, buff);
            WriteAtPosition(6, "6");
            WriteAtPosition(7, "AC On");
            WriteAtPosition(8, "8");
            WriteAtPosition(9, "9");
            WriteAtPosition(10, "10");
            WriteAtPosition(11, "11");
            WriteAtPosition(12, "12");
            break;
        }
        case(1) : {
            WriteAtPosition(0, "PV Charge Info");
            WriteAtPosition(1, "PV Volt");
            sprintf(buff, "%2.1f V ", pv_volt/1000);
            WriteAtPosition(2, buff);
            WriteAtPosition(3, "3");
            WriteAtPosition(4, "PV Curr");
            sprintf(buff, "%2.1fmA ", pv_curr);
            WriteAtPosition(5, buff);
            WriteAtPosition(6, "6");
            WriteAtPosition(7, "Power");
            sprintf(buff, "%2.1fW ", pv_power);
            WriteAtPosition(8, buff);
            WriteAtPosition(9, "9");
            WriteAtPosition(10, "Energy");
            sprintf(buff, "%2.1fWh ", pv_energy);
            WriteAtPosition(11, buff);
            sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
            WriteAtPosition(12, buff);
            break;
        }
        case(2) : {
            WriteAtPosition(0, "Battery Charge Info");
            WriteAtPosition(1, "Bat Volt");
            WriteAtPosition(4, "Bat Curr");
            WriteAtPosition(7, "Power");
            WriteAtPosition(10, "Energy");
            /* Update timer*/
            sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
            WriteAtPosition(12, buff);
            /* Update battery current*/
            sprintf(buff, "%2.1f mA ", battery_curr);
            WriteAtPosition(5, buff);

            /* Update battery voltage*/
            sprintf(buff, "%2.1f V ", battery_volt/1000);
            WriteAtPosition(2, buff);

            /* Update battery power*/
            sprintf(buff, "%2.1fW ", battery_power);
            WriteAtPosition(8, buff);

            /* Update battery energy */
            sprintf(buff, "%3.1fWh", battery_energy);
            WriteAtPosition(11, buff);
            break;
        }
        default:
            break;
    }

    display();
}
   /************************************
    * Method: LCDController::WriteAtPosition
    * Description: Writing a string at specific position
    * There are 12 separate area to choose (position:0->11)
    * so position column is determined by position % 3
    * and position row is determined by position / 3
    * Access: Private
    * Returns:
    * Qualifier:
    ***********************************/
void LCDController::WriteAtPosition(uint8_t pos, const char* data)
{
    const uint16_t cursor_pos_col[3] = { 0, 45, 78 };
    const uint16_t cursor_pos_row[4] = { 18, 30, 42, 54 };
    if(pos == 0)
    {
        setTextCursor(0, 0);
    }
    else
    {
        setTextCursor(cursor_pos_col[(pos-1)%3], cursor_pos_row[(pos-1)/3]);
    }
    printf("%s", data);
    setTextCursor(0, 0);
}

#endif /*_LCDCONTROLLER_H_*/
