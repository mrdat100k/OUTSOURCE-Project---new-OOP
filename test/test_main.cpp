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
#include "TestButton.h"
#include "TestEventHandling.h"
#include "IOPins.h"
/*Initializing i2c object to serve testing process*/
I2CPreInit i2c_object_test(I2C_SDA, I2C_SCL);
/*Initializing a LCD object to test*/
TestLCDController testlcdcontroller(i2c_object_test);
/*Initializing buttons object to test */
TestButton testselecting(SELECT_BUTTON_PIN);
TestButton testsetting(SET_BUTTON_PIN);
TestButton testenable_inverter(INVERTER_ON_PIN);
/*Initializing a INAReader object to test*/
TestINAReader test_measurement(I2C_SDA, I2C_SCL, 0x40);
/*Initializing a RTC_Timer object to test*/
TestRTC_Timer test_rtctimer;
/*Initializing events to test*/
TestEventHandling testeventhandling;

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
    // kiểm tra khi được bấm có tăng biến đếm count không
    testselecting.SetCount(0);
    testselecting.SetButtonLastState(false);
    testselecting.SetButtonCurrentState(false);
    testselecting.TestSampleBTN();
    TEST_ASSERT_EQUAL_INT8(testselecting.GetCount(),1);
    // nhấc nút bấm thì kiểm tra xem phím được nhấn nhanh không
    testselecting.SetButtonCurrentState(true);
    testselecting.TestSampleBTN();
    TEST_ASSERT(testselecting.GetShortPress() == true);
    // tăng count kiểm tra nhấn lâu
    testselecting.SetCount(151);
    testselecting.TestSampleBTN();
    TEST_ASSERT(testselecting.GetLongPress() == true);
}

void pressSetButton(void) {
    // tương tự với các phím còn lại
    testsetting.SetCount(0);
    testsetting.SetButtonLastState(false);
    testsetting.SetButtonCurrentState(false);
    testsetting.TestSampleBTN();
    TEST_ASSERT_EQUAL_INT8(testsetting.GetCount(),1);
    testsetting.SetButtonCurrentState(true);
    testsetting.TestSampleBTN();
    TEST_ASSERT(testsetting.GetShortPress() == true);
    testsetting.SetCount(151);
    testsetting.TestSampleBTN();
    TEST_ASSERT(testsetting.GetLongPress() == true);
}

void pressEnableInverterButton(void) {
    testenable_inverter.SetCount(0);
    testenable_inverter.SetButtonLastState(false);
    testenable_inverter.SetButtonCurrentState(false);
    testenable_inverter.TestSampleBTN();
    TEST_ASSERT_EQUAL_INT8(testenable_inverter.GetCount(),1);
    testenable_inverter.SetButtonCurrentState(true);
    testenable_inverter.TestSampleBTN();
    TEST_ASSERT(testenable_inverter.GetShortPress() == true);
    testenable_inverter.SetCount(151);
    testenable_inverter.TestSampleBTN();
    TEST_ASSERT(testenable_inverter.GetLongPress() == true);
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

void testSwitchMenu() {
    // test đổi màn hình menu
    testeventhandling.SwitchMenuTrigger(false);
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 0);
    testeventhandling.SwitchMenuTrigger(true);
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 1);
    testeventhandling.SwitchMenuTrigger(true);
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 2);
    testeventhandling.SwitchMenuTrigger(true);
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 0);
}
void testEventTimer() {
    //test on off timer
    testeventhandling.InverterTurnOnTrigger(true);
    TEST_ASSERT(testeventhandling.GetInverterTurnOn() == true);
    testeventhandling.InverterTurnOnTrigger(true);
    TEST_ASSERT(testeventhandling.GetInverterTurnOn() == false);
    testeventhandling.InverterTurnOnTrigger(true);
    TEST_ASSERT(testeventhandling.GetInverterTurnOn() == true);
    // test callback menu về màn hình đầu
    testeventhandling.TestTimeoutCallback();
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 0);
}

void connectTestingButtonAndEventHandling() {
    //cho event nhấn nahnh thực hiện xem có đổi màn hình không
    testselecting.SetButtonLastState(false);
    testselecting.SetButtonCurrentState(true);
    testselecting.SetCount(10);
    testselecting.TestSampleBTN();
    testeventhandling.SwitchMenuTrigger(testselecting.GetShortPress());
    TEST_ASSERT(testeventhandling.GetMenuIndex() == 1);
    // tương tự với setbutton xem có đổi on off timer không
    TEST_ASSERT(testeventhandling.GetTimerIsOn() == true);
    testsetting.SetButtonLastState(false);
    testsetting.SetButtonCurrentState(true);
    testsetting.SetCount(10);
    testsetting.TestSampleBTN();
    testeventhandling.TimerIsOnTrigger(testsetting.GetShortPress());
    TEST_ASSERT(testeventhandling.GetTimerIsOn() == false);
    // giữ lâu xem có resettimer không
    testsetting.SetCount(151);
    testsetting.TestSampleBTN();
    testeventhandling.TimerResetTrigger(testsetting.GetLongPress());
    TEST_ASSERT(testeventhandling.GetTimerReset() == true);
    //event on off inverter
    testenable_inverter.SetButtonLastState(false);
    testenable_inverter.SetButtonCurrentState(true);
    testenable_inverter.SetCount(10);
    testenable_inverter.TestSampleBTN();
    testeventhandling.InverterTurnOnTrigger(testenable_inverter.GetShortPress());
    TEST_ASSERT(testeventhandling.GetInverterTurnOn() == false);
}


int main() {
    /*starting a test*/
    UNITY_BEGIN();

    /*===============Test LCD=============*/
    RUN_TEST(setLCDSignalValues);

    RUN_TEST(setLCDTimerValue);

    /*===============Test Button========*/
    RUN_TEST(pressSelectButton);

    RUN_TEST(pressSetButton);

    RUN_TEST(pressEnableInverterButton);
    /*===============Test INA Module======*/

    RUN_TEST(setINAOutOfRangeValue);

    /*===============Test Timer===========*/
    RUN_TEST(resetTimer);

    RUN_TEST(changeTimerState);

    RUN_TEST(updateTimerValue);

    RUN_TEST(testSwitchMenu);

    RUN_TEST(testEventTimer);

    RUN_TEST(connectTestingLCDAndINA);

    RUN_TEST(connectTestingLCDAndRTCTimer);

    RUN_TEST(connectTestingButtonAndEventHandling);
    /*finish this test*/

    UNITY_END();
    while (1) {}
}
#endif
