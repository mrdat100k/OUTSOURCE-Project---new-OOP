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
#include <mbed.h>
#include <unity.h>
#include "INAReader.h"
#include "LCDController.h"
#include "RTCTimer.h"
#include "KeyboardController.h"
#include "IOPins.h"
#ifdef UNIT_TEST
/*Initializing i2c object to serve testing process*/
I2CPreInit i2c_object_test(I2C_SDA, I2C_SCL);
/*Initializing a LCD object to test*/
LCDController testlcdcontroller(i2c_object_test);
/*Initializing a keyboard object to test */
KeyboardController testkeyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
/*Initializing a INAReader object to test*/
INAReader test_measurement(I2C_SDA, I2C_SCL, 0x40);
/*Initializing a RTC_Timer object to test*/
RTC_Timer test_rtctimer;
void DisplayLCD_WhenChangingBatteryParameters_ChangingParametersToDisplay(void)
{   /*All of these should pass */
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
}

void DisplayLCD_WhenChangingPVParameters_ChangingParametersToDisplay(void)
{   /* All of these should pass */
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

void DisplayLCD_WhenChangingTimerParameters_ChangingParametersToDisplay(void)
{   /*All of these should pass */
    /*Calling SetTime method of testlcdcontroller object*/
    testlcdcontroller.SetTime(23,59,59);
    /*Checking the time value set */
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 23);
}

void PressingKeyboard_WhenMenuButtonIsPressed_ChangingMenuParameter(void)
{   /* All of these should pass */
    /*Calling AtTimeOut method of testkeyboard object*/
    testkeyboard.AtTimeOut();
    /*Calling OnSelectButtonPressFallIsr method of testkeyboard object*/ 
    testkeyboard.OnSelectButtonPressFallIsr();
    /*Checking menu index */ 
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 1);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 2);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 0);
}

void PressingKeyboard_WhenChangingTimerStateButtonIsPressed_ChangingTimerParameters(void)
{   /* All of these should pass */
    /*Calling Setmenuindex method of testkeyboard object*/
    testkeyboard.Setmenuindex(1);
    /*Calling OnSelectButtonPressFallIsr method of testkeyboard object*/ 
    testkeyboard.OnSetButtonPressFallIsr();
    /*Checking timer status */
    TEST_ASSERT(testkeyboard.Gettimeron() == true);
    testkeyboard.Setmenuindex(2);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == false);
}

void MethodsOfINA_WhenCallingMethods_CheckingInputValues(void)
{   /* All of these should pass */
    /*Calling Calibrate method of test_measurement object to change max voltage value,
     *max current value, shunt resistor value.
     */
    test_measurement.Calibrate(0.1, 3.2, 32);
    /*changing voltage input value*/
    test_measurement.GetVolt(32.1);
    /*changing curent input value*/
    test_measurement.GetCurr(3.3);
    test_measurement.TestScanning();
    /*Checking permission of voltage input value*/
    TEST_ASSERT(test_measurement.Get_voltage_out_of_range() == true);
    /*Checking permission of current input value*/
    TEST_ASSERT(test_measurement.Get_current_out_of_range() == true);
}

void ResetRTCtimer_WhenResetTimer_ResetTimerValues(void)
{   /* All of these should pass */
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

void StateTimer_WhenChangingTimerState_ChangingtimerState(void)
{   /*All of these should pass */  
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

void UpdateRTCtimer_WhenUpdatingTimerValues_ChaningTimerValues(void)
{   /*All of these should pass */ 
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

int main()
{  /*starting a test*/
    UNITY_BEGIN();

    RUN_TEST(DisplayLCD_WhenChangingBatteryParameters_ChangingParametersToDisplay);

    RUN_TEST(DisplayLCD_WhenChangingPVParameters_ChangingParametersToDisplay);

    RUN_TEST(DisplayLCD_WhenChangingTimerParameters_ChangingParametersToDisplay);

    RUN_TEST(PressingKeyboard_WhenMenuButtonIsPressed_ChangingMenuParameter);

    RUN_TEST(PressingKeyboard_WhenChangingTimerStateButtonIsPressed_ChangingTimerParameters);

    RUN_TEST(MethodsOfINA_WhenCallingMethods_CheckingInputValues);

    RUN_TEST(ResetRTCtimer_WhenResetTimer_ResetTimerValues);

    RUN_TEST(RUN_TEST(StateTimer_WhenChangingTimerState_ChangingtimerState);

    RUN_TEST(UpdateRTCtimer_WhenUpdatingTimerValues_ChaningTimerValues);
    /*finish this test*/
    UNITY_END();
    while(1){}
}

#endif
