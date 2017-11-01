/******************************************************************************
 * @file    main.cpp
 * @author  Dua Nguyen
 * @brief     Functional testing: reading current value, voltage value, power value from INA module
 * time update, display content on screen, press button to go next screen, reSet timer.
 * TODO: long description
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 */
 /*****************************************************************************
 * INA219 module to measure battery and PV basic functionality including initialization, Calibration,
 * reading current value, voltage value, power value and energy in period time

 Hardware setup:
 INA219 for battery and PV
 INA219 --------- Nucleo L432 board
 3.3V --------------------- 3.3V
 SDA ----------------------- I2C_SDA (PB_7)
 SCL ----------------------- I2C_SCL (PB_6)
 GND ---------------------- GND
 Note: using 2 INA219 modules for measuring battery and PV. so user have to set different address
 from 0x40 to 0x4f. in this project, we set 0x40 for battery and 0x41 for PV
 */
 /*****************************************************************************
 * LCD Adafruit_oled 128x64 basic functionality including initialization, show a specific logo,
 * show information about current, voltage, power and energy value.
 Hardware setup:
 LCD Adafruit_oled 128x64
 LCD Adafruit_oled 128x64 --------- Nucleo L432 board
 3.3V --------------------- 3.3V
 SDA ----------------------- I2C_SDA (PB_7)
 SCL ----------------------- I2C_SCL (PB_6)
 GND ---------------------- GND
 note: LCD I2C address : 0x78
 */
 /*****************************************************************************
 * KeyboardController functionality including changing the status of system such as
   changing menu screean, starting timer, stopping timer, selecting inverter mode
   Hardware setup:
   SELECT_BUTTON_PIN ------------PB_0
   SET_BUTTON_PIN ---------------PB_1
   INVERTER_ON_PIN --------------PB_2
  */
 /*****************************************************************************
  * RTCtimer functionality including count a period time to calculate energy of battery
    and PV
 *****************************************************************************/
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
    while (true) {
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
#endif /*UNIT_TEST*/
