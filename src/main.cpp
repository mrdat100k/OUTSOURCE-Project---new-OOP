/*!
 * \file main.cpp
 * \date 2017/10/06
 *
 * \author
 * Contact:
 *
 * \brief
 *
 * TODO: long description
 * Functional testing: reading current value, voltage value, power value from INA module,
 * time update, display content on screen, press button to go next screen, reSet timer.
 *
 * \note
*/

#include <mbed.h>
#include <var.h>    /*Store global variable for interacting with hardware*/
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
/*initialization lcd object*/
LCDController lcdcontroller(&g_lcd_object);
/*initialization current, voltage measuring object*/
INAReader ina_reader(&g_battery_measure_object, &g_pv_measure_object);
/*initialization keyboard object*/
KeyboardController keyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
/*initialization realtime clock object */
RTC_Timer rtc_timer;
int main() {
    /*Display logo watershed on screen*/
    lcdcontroller.ShowLogo();
    /*calibrate ina219 with 0.1 ohm Shunt, max current 3.2A, max voltage 32V*/
    ina_reader.Calibration(0.1, 3.2, 32);
    /*Wait for 3 seconds*/
    wait(3);
    while(true)
    {
        /*Reading values from INA module*/
        ina_reader.Scan();
        /*updating realtime clock*/
        rtc_timer.Update();
        /*updating properties of lcd object */
        lcdcontroller.SetBattVolt(ina_reader.GetBattVolt());
        lcdcontroller.SetBattCurr(ina_reader.GetBattCurr());
        lcdcontroller.SetBattPower(ina_reader.GetBattPower());
        lcdcontroller.SetPVVolt(ina_reader.GetPVVolt());
        lcdcontroller.SetPVCurr(ina_reader.GetPVCurr());
        lcdcontroller.SetPVPower(ina_reader.GetPVPower());
        lcdcontroller.SetTime(rtc_timer.GetHour(), rtc_timer.GetMinute(), rtc_timer.GetSecond());
        /*selecting screen to display*/
        lcdcontroller.UpdateScreen(keyboard.menu_index);
    }
}
