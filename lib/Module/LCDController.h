/*!
 *  File LCDController.h
 *  This file consist of classes which use to manage content on screen
 *  and the screen is controlled to display three separate menu
 * Date October 2017
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
    /**
    *@brief
    *@param second 
    *@param minute
    *@param hour
    *Second value, minute value, hour value start 0. when pressing button, it starts to increase
    *it's updated continuously to display on screen
    *@param cursor_pos_col Column position array
    *@param cursor_pos_row row position array
    *The screen is divided to 12 separate area
    *so we need 3 column and 4 row position values to locate a specific area
    /*
    Adjust measurement range
    */
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
    void WriteAtPosition(uint8_t pos, const char* data);
};
    //************************************
    // Method: LCDController::ShowLogo
    // Description: Showing a specific logo on screen
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::ShowLogo()
{
    lcd_object_ptr -> clearDisplay();
    lcd_object_ptr -> drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
    lcd_object_ptr -> display();
}
    //************************************
    // Method: LCDController::SetPVVolt
    // Description: Updating PV voltage value to display
    // Access: public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetPVVolt(float value)
{
    pv_volt = value;
}
    //************************************
    // Method: LCDController::SetPVCurr
    // Description: updating PV current value to display
    // Access: public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetPVCurr(float value)
{
    pv_curr = value;
}
    //************************************
    // Method: LCDController::SetPVPower
    // Description: Updating PV power value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetPVPower(float value)
{
    pv_power = value;
}
    //************************************
    // Method: LCDController::SetPVEnergy
    // Description: Updating PV energy value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetPVEnergy(float value)
{
    pv_energy = value;
}
    //************************************
    // Method: LCDController::SetBattVolt
    // Description: Updating battery voltage value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetBattVolt(float value)
{
    battery_volt = value;
}
    //************************************
    // Method: LCDController::SetBattCurr
    // Description: Updating battery current value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetBattCurr(float value)
{
    battery_curr = value;
}
    //************************************
    // Method: LCDController::SetBattPower
    // Description: Updating battery power value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetBattPower(float value)
{
    battery_power = value;
}
    //************************************
    // Method: LCDController::SetBattEnergy
    // Description: Updating battery energy value to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetBattEnergy(float value)
{
    battery_energy = value;
}
    //************************************
    // Method: LCDController::SetTime
    // Description: Updating time to display
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    hour = _hour;
    minute = _minute;
    second = _second;
}
    //************************************
    // Method: LCDController::UpdateScreen
    // Description: Change menu screen
    // There are 3 different menu screen
    // Before updating a new screen, we need to call clearing display function
    // @para screen_index The variable determine which menu screen is displayed
    // Access: Public
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::UpdateScreen(uint8_t screen_index)
{
    char buff[12]; /*Data buffer*/
    lcd_object_ptr -> clearDisplay();
    /* Update screen contents */
    switch (screen_index)
    {
        case(0) : {

            //TODO: viet not
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
            //TODO: viet not
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

    lcd_object_ptr -> display();
}
    //************************************
    // Method: LCDController::WriteAtPosition
    // Description: Writing a string at specific possition
    // 
    // Access: Private
    // Returns:
    // Qualifier:
    //***********************************
void LCDController::WriteAtPosition(uint8_t pos, const char* data)
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
