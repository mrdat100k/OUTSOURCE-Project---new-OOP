/*!
 * \file LCDController.h
 * \Lớp đối tượng màn hình
 * \Lớp đối tượng quản lý các thông tin hiển thị trên màn hình
 * \Chia màn hình hiển thị thành 3 menu
 * \author
 *
 * \date October 2017
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
    LCDController(Adafruit_SSD1306_I2c *pointer):
        pv_volt(0), pv_curr(0), pv_power(0), pv_energy(0),
        battery_volt(0), battery_curr(0), battery_power(0), battery_energy(0),
        second(0), minute(0), hour(0),
	    cursor_pos_col{ 0, 45, 78 },
        cursor_pos_row{ 18, 30, 42, 54 }
    {
        lcd_object_ptr = pointer;
    }
    /*
    hiển thị logo
    */
    void showLogo();

    void setPVVolt(float value);

    void setPVCurr(float value);

    void setPVPower(float value);

    void setPVEnergy(float value);

    void setBattVolt(float value);

    void setBattCurr(float value);

    void setBattPower(float value);

    void setBattEnergy(float value);

    void  updateScreen(uint8_t screen_index);

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

void LCDController::showLogo()
{
    lcd_object_ptr -> clearDisplay();
    lcd_object_ptr -> drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
    lcd_object_ptr -> display();
}
void LCDController::setPVVolt(float value)
{
    pv_volt = value;
}
void LCDController::setPVCurr(float value)
{
    pv_curr = value;
}
void LCDController::setPVPower(float value)
{
    pv_power = value;
}
void LCDController::setPVEnergy(float value)
{
    pv_energy = value;
}
void LCDController::setBattVolt(float value)
{
    battery_volt = value;
}
void LCDController::setBattCurr(float value)
{
    battery_curr = value;
}
void LCDController::setBattPower(float value)
{
    battery_power = value;
}
void LCDController::setBattEnergy(float value)
{
    battery_energy = value;
}
void LCDController::setTime(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    hour = _hour;
    minute = _minute;
    second = _second;
}
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
