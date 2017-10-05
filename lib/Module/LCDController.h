/*!
 *  File LCDController.h
 *  This file consist of classes which use to manage content on screen
 *  and divide screen to become three separate area
 *  
 *
 * Date October 2017
 *
 *
 */
#ifndef _LCDCONTROLLER_H_
#define _LCDCONTROLLER_H_
#include <Adafruit_SSD1306.h>
#include <logo.h>
class LCDController
{
public:
    //************************************
    // Method:    LCDController::LCDController
    // Description:   LCDController constructor
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
    LCDController(Adafruit_SSD1306_I2c *pointer):
        pv_volt(0), pv_curr(0), pv_power(0), pv_energy(0),
        battery_volt(0), battery_curr(0), battery_power(0), battery_energy(0),
        second(0), minute(0), hour(0),
	cursor_pos_col{ 0, 45, 78 },
        cursor_pos_row{ 18, 30, 42, 54 }
    {
        lcd_object_ptr = pointer;
    }
    /*display specific logo on LCD*/
    void showLogo();
    /*update PV voltage value to display */
    void setPVVolt(float value);
    /*update PV current value to display */
    void setPVCurr(float value);
    /*update PV power value to display */
    void setPVPower(float value);
    /*update PV energy value to display */
    void setPVEnergy(float value);
    /*update battery voltage value to display */
    void setBattVolt(float value);
    /*update battery current value to display */
    void setBattCurr(float value);
    /*update battery power value to display */
    void setBattPower(float value);
    /*update battery energy value to display */
    void setBattEnergy(float value);
    /*Change content on screen */
    void  updateScreen(uint8_t screen_index);
    /*setting timer value*/
    void setTime(uint8_t _hour, uint8_t _minute, uint8_t _second);

private:
    float pv_volt;
    float pv_curr;
    float pv_power;
    float pv_energy;
    float battery_volt;
    float battery_curr;
    float battery_power;
    float battery_energy;
    Adafruit_SSD1306_I2c *lcd_object_ptr;
    uint8_t second, minute, hour;
    uint16_t cursor_pos_col[3], cursor_pos_row[4];
    void writeAtPosition(uint8_t pos, const char* data);
};
    //************************************
    // Method:    LCDController::showLogo
    // Description:    showing a specific logo on screen
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::showLogo()
{
    lcd_object_ptr -> clearDisplay();
    lcd_object_ptr -> drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
    lcd_object_ptr -> display();
}
    //************************************
    // Method:    LCDController::setPVVolt
    // Description:    updating PV voltage value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setPVVolt(float value)
{
    pv_volt = value;
}
    //************************************
    // Method:    LCDController::setPVCurr
    // Description:    updating PV current value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setPVCurr(float value)
{
    pv_curr = value;
}
    //************************************
    // Method:    LCDController::setPVPower
    // Description:    updating PV power value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setPVPower(float value)
{
    pv_power = value;
}
    //************************************
    // Method:    LCDController::setPVEnergy
    // Description:    updating PV energy value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setPVEnergy(float value)
{
    pv_energy = value;
}
    //************************************
    // Method:    LCDController::setBattVolt
    // Description:    updating battery voltage value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setBattVolt(float value)
{
    battery_volt = value;
}
    //************************************
    // Method:    LCDController::setBattCurr
    // Description:    updating battery current value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setBattCurr(float value)
{
    battery_curr = value;
}
    //************************************
    // Method:    LCDController::setBattPower
    // Description:    updating battery power value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setBattPower(float value)
{
    battery_power = value;
}
    //************************************
    // Method:    LCDController::setBattEnergy
    // Description:    updating battery energy value to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setBattEnergy(float value)
{
    battery_energy = value;
}
    //************************************
    // Method:    LCDController::setTime
    // Description:    updating time to display
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::setTime(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    hour = _hour;
    minute = _minute;
    second = _second;
}
    //************************************
    // Method:    LCDController::updateScreen
    // Description:    change menu screen 
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::updateScreen(uint8_t screen_index)
{
    char buff[12]; /*Data buffer*/
    lcd_object_ptr -> clearDisplay();

    /* Update screen contents */
    switch (screen_index)
    {
        case(0) : {

            //TODO: viet not
            writeAtPosition(0, "MAIN MENU");
            writeAtPosition(1, "Charge");
            writeAtPosition(2, "Yes");
            writeAtPosition(3, "DC");
            writeAtPosition(4, "Battery");
            sprintf(buff, "%2.1fV ", battery_volt/1000);
            writeAtPosition(5, buff);
            writeAtPosition(6, "6");
            writeAtPosition(7, "AC On");
            writeAtPosition(8, "8");
            writeAtPosition(9, "9");
            writeAtPosition(10, "10");
            writeAtPosition(11, "11");
            writeAtPosition(12, "12");
            break;
        }
        case(1) : {
            //TODO: viet not
            writeAtPosition(0, "PV Charge Info");
            writeAtPosition(1, "PV Volt");
            sprintf(buff, "%2.1f V ", pv_volt/1000);
            writeAtPosition(2, buff);
            writeAtPosition(3, "3");
            writeAtPosition(4, "PV Curr");
            sprintf(buff, "%2.1fmA ", pv_curr);
            writeAtPosition(5, buff);
            writeAtPosition(6, "6");
            writeAtPosition(7, "Power");
            sprintf(buff, "%2.1fW ", pv_power);
            writeAtPosition(8, buff);
            writeAtPosition(9, "9");
            writeAtPosition(10, "Energy");
            sprintf(buff, "%2.1fWh ", pv_energy);
            writeAtPosition(11, buff);
            sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
            writeAtPosition(12, buff);
            break;
        }
        case(2) : {
            writeAtPosition(0, "Battery Charge Info");
            writeAtPosition(1, "Bat Volt");
            writeAtPosition(4, "Bat Curr");
            writeAtPosition(7, "Power");
            writeAtPosition(10, "Energy");
            /* Update timer*/
            sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
            writeAtPosition(12, buff);
            /* Update battery current*/
            sprintf(buff, "%2.1f mA ", battery_curr);
            writeAtPosition(5, buff);

            /* Update battery voltage*/
            sprintf(buff, "%2.1f V ", battery_volt/1000);
            writeAtPosition(2, buff);

            /* Update battery power*/
            sprintf(buff, "%2.1fW ", battery_power);
            writeAtPosition(8, buff);

            /* Update battery energy */
            sprintf(buff, "%3.1fWh", battery_energy);
            writeAtPosition(11, buff);
            break;
        }
        default:
            break;
    }

    lcd_object_ptr -> display();
}
   //************************************
    // Method:    LCDController::writeAtPosition
    // Description:    writing a string at specific possition
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::writeAtPosition(uint8_t pos, const char* data)
{
    if(pos == 0)
    {
        lcd_object_ptr -> setTextCursor(0, 0);
    }
    else
    {
        lcd_object_ptr -> setTextCursor(cursor_pos_col[(pos-1)%3], cursor_pos_row[(pos-1)/3]);
    }
    lcd_object_ptr -> printf("%s", data);
    lcd_object_ptr -> setTextCursor(0, 0);
}

#endif /*_LCDCONTROLLER_H_*/
