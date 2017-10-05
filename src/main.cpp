/* 
* Functional testing: reading current value, voltage value, power value from INA module,  
* time update, display content on screen, press button to go next screen, reset timer.
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
    lcdcontroller.showLogo();
    wait(3);
    while(true) 
    {
        /*Reading values from INA module*/
        ina_reader.Scan();
        /*updating realtime clock*/
        rtc_timer.Update();
        /*updating properties of lcd object */
        lcdcontroller.setBattVolt(ina_reader.getBattVolt());
        lcdcontroller.setBattCurr(ina_reader.getBattCurr());
        lcdcontroller.setBattPower(ina_reader.getBattPower());
        lcdcontroller.setPVVolt(ina_reader.getPVVolt());
        lcdcontroller.setPVCurr(ina_reader.getPVCurr());
        lcdcontroller.setPVPower(ina_reader.getPVPower());
        lcdcontroller.setTime(rtc_timer.GetHour(), rtc_timer.GetMinute(), rtc_timer.GetSecond());
        /*selecting screen to display*/
        lcdcontroller.updateScreen(keyboard.menu_index);
    }
}
