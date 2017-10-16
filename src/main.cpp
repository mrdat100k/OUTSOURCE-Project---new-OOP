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

#include <IOPins.h>
#include <mbed.h>
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
#ifndef UNIT_TEST
/*initialization lcd object*/
I2CPreInit i2c_object(I2C_SDA, I2C_SCL);
LCDController lcdcontroller(i2c_object);
/*initialization current, voltage measuring object*/
INAReader battery_measurement(I2C_SDA, I2C_SCL, 0x40);
INAReader pv_measurement(I2C_SDA, I2C_SCL, 0x41);
/*initialization keyboard object*/
KeyboardController keyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
/*initialization realtime clock object */
RTC_Timer rtc_timer;

int main() {
    /*Display logo watershed on screen*/
    lcdcontroller.ShowLogo();
    /*calibrate ina219 with 0.1 ohm Shunt, max current 3.2A, max voltage 32V*/
    battery_measurement.Calibrate(0.1, 3.2, 32);
    pv_measurement.Calibrate(0.1, 3.2, 32);
    /*Wait for 3 seconds*/
    wait(3);
    while(true)
    {
        /*Reading values from INA module*/
        battery_measurement.Scan();
        pv_measurement.Scan();
        /*updating realtime clock*/
        rtc_timer.Update();
        /*updating properties of lcd object */
        lcdcontroller.SetBattVolt(battery_measurement.GetVolt());
        lcdcontroller.SetBattCurr(battery_measurement.GetCurr());
        lcdcontroller.SetBattPower(battery_measurement.GetPower());
        lcdcontroller.SetPVVolt(pv_measurement.GetVolt());
        lcdcontroller.SetPVCurr(pv_measurement.GetCurr());
        lcdcontroller.SetPVPower(pv_measurement.GetPower());
        lcdcontroller.SetTime(rtc_timer.GetHour(), rtc_timer.GetMinute(), rtc_timer.GetSecond());
        /*selecting screen to display*/
        lcdcontroller.UpdateScreen(keyboard.menu_index);
    }
}
#endif
