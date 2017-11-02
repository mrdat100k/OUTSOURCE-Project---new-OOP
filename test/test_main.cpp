/******************************************************************************
 * @file    test_main.cpp
 * @author  Dua Nguyen
 * @brief  This file include: LCD displaying test by changing
 *         timer, PV and battery parameters to show; keyboard test;
 *         INA219 test by calibrating, setting and reading parameters
 *         and RTC timer test.
 * TODO: long description
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 ****************************************************************************/
#ifdef UNIT_TEST
#include <mbed.h>
#include <unity.h>
#include "TestINAReader.h"
#include "TestLCDController.h"
#include "TestRTC_Timer.h"
#include "TestKeyboardController.h"
#include "IOPins.h"
/*Initializing i2c object to serve testing process*/
I2CPreInit i2c_object_test(I2C_SDA, I2C_SCL);
/*Initializing a LCD object to test*/
TestLCDController testlcdcontroller(i2c_object_test);
/*Initializing a keyboard object to test */
TestKeyboardController testkeyboard(SELECT_BUTTON_PIN,
SET_BUTTON_PIN,
INVERTER_ON_PIN);
/*Initializing a INAReader object to test*/
TestINAReader test_measurement(I2C_SDA, I2C_SCL, 0x40);
/*Initializing a RTC_Timer object to test*/
TestRTC_Timer test_rtctimer;


void setLCDSignalValues(void) {
    /*All of these should pass */
    /*Calling SetBattVolt method of testlcdcontroller object*/
    testlcdcontroller.SetBattVolt(10);
    /*Checking new voltage value of battery */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattVolt(), 10);
    /*Calling SetBattCurr method of testlcdcontroller object*/
    testlcdcontroller.SetBattCurr(30);
    /*Checking new current value of battery */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattCurr(), 30);
    /*Calling SetBattPower method of testlcdcontroller object*/
    testlcdcontroller.SetBattPower(30);
    /*Checking new power value of battery */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattPower(), 30);
    /*Calling SetBattEnergy method of testlcdcontroller object*/
    testlcdcontroller.SetBattEnergy(30);
    /*Checking new energy value of battery */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattEnergy(), 30);
    /*Calling SetPVVolt method of testlcdcontroller object*/
    testlcdcontroller.SetPVVolt(10);
    /*Checking new voltage value of PV */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVVolt(), 10);
    /*Calling SetPVCurr method of testlcdcontroller object*/
    testlcdcontroller.SetPVCurr(30);
    /*Checking new current value of PV */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVCurr(), 30);
    /*Calling SetPVPower method of testlcdcontroller object*/
    testlcdcontroller.SetPVPower(30);
    /*Checking new power value of PV */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVPower(), 30);
    /*Calling SetPVEnergy method of testlcdcontroller object*/
    testlcdcontroller.SetPVEnergy(30);
    /*Checking new energy value of PV */
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVEnergy(), 30);
}


void setLCDTimerValue(void) {
    /*All of these should pass */
    /*Calling SetTime method of testlcdcontroller object*/
    testlcdcontroller.SetTime(23, 59, 59);
    /*Checking the time value set */
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 23);
}

void pressSelectButton(void) {
    /* All of these should pass */
    /*Calling AtTimeOut method of testkeyboard object*/
    testkeyboard.TestAtTimeOut();
    /*Calling OnSelectButtonPressFallIsr method of testkeyboard object*/
    testkeyboard.TestOnSelectButtonPressFallIsr();
    /*Checking menu index */
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 1);
    testkeyboard.TestOnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 2);
    testkeyboard.TestOnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 0);
}

void pressSetButton(void) {
    /* All of these should pass */
    /*Calling Setmenuindex method of testkeyboard object*/
    testkeyboard.Setmenuindex(1);
    /*Calling OnSelectButtonPressFallIsr method of testkeyboard object*/
    testkeyboard.TestOnSetButtonPressFallIsr();
    /*Checking timer status */
    TEST_ASSERT(testkeyboard.Gettimeron() == true);
    testkeyboard.Setmenuindex(2);
    testkeyboard.TestOnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == false);
}

void setINAOutOfRangeValue(void) {
    /* All of these should pass */
    /*Calling Calibrate method of test_measurement object to change max voltage value,
     *max current value, shunt resistor value.
     */
    test_measurement.Calibrate(0.1, 3.19, 32);
    /*changing voltage input value*/
    test_measurement.SetVolt(32.1);
    /*changing curent input value*/
    test_measurement.SetCurr(3.3);
    test_measurement.TestScanning();
    /*Checking permission of voltage input value*/
    TEST_ASSERT(test_measurement.Get_voltage_out_of_range() == true);
    /*Checking permission of current input value*/
    TEST_ASSERT(test_measurement.Get_current_out_of_range() == true);
}

void resetTimer(void) {
    /* All of these should pass */
    /*Reseting RTC timer value*/
    test_rtctimer.Reset();
    /*checking status of RTC timer*/
    TEST_ASSERT(test_rtctimer.GetState() == true);
    /*checking second value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetSecond(), 0);
    /*checking minute value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetMinute(), 0);
    /*checking hour value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetHour(), 0);
}

void changeTimerState(void) {
    /*All of these should pass */
    /*Turning on rtc timer*/
    test_rtctimer.On();
    /*checking new status of RTC timer*/
    TEST_ASSERT(test_rtctimer.GetState() == true);
    /*Turning off rtc timer*/
    test_rtctimer.Off();
    /*checking new status of RTC timer*/
    TEST_ASSERT(test_rtctimer.GetState() == false);
    /*reversing current status of RTC timer*/
    test_rtctimer.ChangeState();
    /*checking new status of RTC timer*/
    TEST_ASSERT(test_rtctimer.GetState() == true);
}

void updateTimerValue(void) {
    /*All of these should pass */
    /*setting timer value*/
    set_time(43199);
    test_rtctimer.Update();
    /*checking second value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetSecond(), 59);
    /*checking minute value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetMinute(), 59);
    /*checking hour value of RTC timer*/
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetHour(), 11);
}

void connectTestingLCDAndINA(void) { //hàm test kết nối giữa lcd và ina
    /*changing voltage input value*/
    test_measurement.SetVolt(15.1);
    /*changing curent input value*/
    test_measurement.SetCurr(1.3);
    /*changing power input value*/
    test_measurement.SetPower(40);
    /*đưa các giá trị ra màn hình từ INA*/
    testlcdcontroller.SetBattVolt(test_measurement.GetVolt());

    testlcdcontroller.SetBattCurr(test_measurement.GetCurr());

    testlcdcontroller.SetBattPower(test_measurement.GetPower());
    /*kiểm tra xem giá trị của LCD đúng không*/
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattVolt(), 15.1);

    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattCurr(), 1.3);

    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattPower(), 40);
    /* tương tự với PV*/
    testlcdcontroller.SetPVVolt(test_measurement.GetVolt());

    testlcdcontroller.SetPVCurr(test_measurement.GetCurr());

    testlcdcontroller.SetPVPower(test_measurement.GetPower());

    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVVolt(), 15.1);

    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVCurr(), 1.3);

    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVPower(), 40);
}

void connectTestingLCDAndRTCTimer() { //hàm kiểm tra giữa lcd và timer
    /*setting timer value*/
    set_time(43199);
    /*updating realtime clock*/
    test_rtctimer.Update();
    /* đặt các giá trị của RTC vào lcd*/
    testlcdcontroller.SetTime(test_rtctimer.GetHour(), test_rtctimer.GetMinute(), test_rtctimer.GetSecond());
    /* Kiểm tra trên Lcd giờ phút giấy*/
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 11);
}

void connectTestingKeyboard_LCD_RTCtimer() { // kết hợp lcd timer và phim bấm
    /*Calling Setmenuindex method of testkeyboard object*/
    testkeyboard.Setmenuindex(1);
    /*setting timer value*/
    set_time(43199);
    /*updating realtime clock*/
    test_rtctimer.Update();

    testlcdcontroller.SetTime(test_rtctimer.GetHour(), test_rtctimer.GetMinute(), test_rtctimer.GetSecond());

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 11);
    /*giữ lâu để reset timer*/
    testkeyboard.TestOnsetButtonLongPress();
    /*updating realtime clock*/
    test_rtctimer.Update();

    testlcdcontroller.SetTime(test_rtctimer.GetHour(), test_rtctimer.GetMinute(), test_rtctimer.GetSecond());

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 0);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 0);

    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 0);
}


int main() {
    /*starting a test*/
    UNITY_BEGIN();

    /*===============Test LCD=============*/
    RUN_TEST(setLCDSignalValues);

    RUN_TEST(setLCDTimerValue);

    /*===============Test Keyboard========*/
    RUN_TEST(pressSelectButton);

    RUN_TEST(pressSetButton);

    /*===============Test INA Module======*/
    RUN_TEST(setINAOutOfRangeValue);

    /*===============Test Timer===========*/
    RUN_TEST(resetTimer);

    RUN_TEST(changeTimerState);

    RUN_TEST(updateTimerValue);

    RUN_TEST(connectTestingLCDAndINA);

    RUN_TEST(connectTestingLCDAndRTCTimer);

    RUN_TEST(connectTestingKeyboard_LCD_RTCtimer);
    /*finish this test*/

    UNITY_END();
    while (1) {}
}
#endif
