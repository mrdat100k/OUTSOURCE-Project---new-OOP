#include <mbed.h>
#include <var.h>
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
LCDController lcdcontroller(&g_lcd_object);
INAReader ina_reader(&g_battery_measure_object, &g_pv_measure_object);
KeyboardController keyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
RTC_Timer rtc_timer;
int main() {

    // put your setup code here, to run once:
    lcdcontroller.showLogo();
    wait(3);
    while(1) {
        // put your main code here, to run repeatedly:
        ina_reader.Scan();
        rtc_timer.Update();
        lcdcontroller.setBattVolt(ina_reader.getBattVolt());
        lcdcontroller.setBattCurr(ina_reader.getBattCurr());
        lcdcontroller.setBattPower(ina_reader.getBattPower());
        lcdcontroller.setPVVolt(ina_reader.getPVVolt());
        lcdcontroller.setPVCurr(ina_reader.getPVCurr());
        lcdcontroller.setPVPower(ina_reader.getPVPower());
        lcdcontroller.setTime(rtc_timer.GetHour(), rtc_timer.GetMinute(), rtc_timer.GetSecond());
        lcdcontroller.updateScreen(keyboard.menu_index);
    }
}
