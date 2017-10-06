/*
* Functional testing: reading current value, voltage value, power value from INA module,
* time update, display content on screen, press button to go next screen, reSet timer.
*
*/
#include <mbed.h>
#include <var.h>
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
/*initialization lcd object*/
LCDController lcdcontroller(&g_lcd_object);
/*initialization measuring object */
INAReader ina_reader(&g_battery_measure_object, &g_pv_measure_object);
/*initialization keyboard object*/
KeyboardController keyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
/*initialization realtime clock object */
RTC_Timer rtc_timer;
int main() {
    /*Display logo watershed on screen*/
    lcdcontroller.ShowLogo();
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
