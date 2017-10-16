#include <mbed.h>
#include <unity.h>

#include "INAReader.h"
#include "LCDController.h"
#include "RTCTimer.h"
#include "KeyboardController.h"
#include "IOPins.h"



#ifdef UNIT_TEST


I2CPreInit i2c_object_test(I2C_SDA, I2C_SCL);
LCDController testlcdcontroller(i2c_object_test);
KeyboardController testkeyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
INAReader test_measurement(I2C_SDA, I2C_SCL, 0x40);
RTC_Timer test_rtctimer;

void test_LCD_Batt(void)
{
    testlcdcontroller.SetBattVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattVolt(), 10);
    testlcdcontroller.SetBattCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattCurr(), 30);
    testlcdcontroller.SetBattPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattPower(), 30);
    testlcdcontroller.SetBattEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattEnergy(), 30);
}

void test_LCD_PV(void)
{
    testlcdcontroller.SetPVVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVVolt(), 10);
    testlcdcontroller.SetPVCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVCurr(), 30);
    testlcdcontroller.SetPVPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVPower(), 30);
    testlcdcontroller.SetPVEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVEnergy(), 30);
}

void test_LCD_Time(void)
{
    testlcdcontroller.SetTime(23,59,59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 23);
}

void test_Keyboard_selectbutton(void)
{
    testkeyboard.AtTimeOut();
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 1);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 2);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 0);
}

void test_Keyboard_setbutton(void)
{
    testkeyboard.Setmenuindex(1);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == true);
    testkeyboard.Setmenuindex(2);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == false);
}

void test_INA(void)
{
    test_measurement.Calibrate(0.1, 3.2, 32);
    test_measurement.GetVolt(32.1);
    test_measurement.GetCurr(3.3);
    test_measurement.TestScanning();
    TEST_ASSERT(test_measurement.Get_voltage_out_of_range() == true);
    TEST_ASSERT(test_measurement.Get_current_out_of_range() == true);
}

void test_RTCtimer_Reset(void)
{
    test_rtctimer.Reset();
    TEST_ASSERT(test_rtctimer.GetState() == true);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetSecond(), 0);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetMinute(), 0);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetHour(), 0);


}

void test_RTCtimer_State(void)
{
    test_rtctimer.On();
    TEST_ASSERT(test_rtctimer.GetState() == true);
    test_rtctimer.Off();
    TEST_ASSERT(test_rtctimer.GetState() == false);
    test_rtctimer.ChangeState();
    TEST_ASSERT(test_rtctimer.GetState() == true);
}

void test_RTCtimer_Update(void)
{
    set_time(43199);
    test_rtctimer.Update();
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetSecond(), 59);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetMinute(), 59);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetHour(), 11);
}

int main()
{

    UNITY_BEGIN();

    RUN_TEST(test_LCD_Batt);

    RUN_TEST(test_LCD_PV);

    RUN_TEST(test_LCD_Time);

    RUN_TEST(test_Keyboard_setbutton);

    RUN_TEST(test_Keyboard_selectbutton);

    RUN_TEST(test_INA);

    RUN_TEST(test_RTCtimer_Update);

    RUN_TEST(test_RTCtimer_State);

    RUN_TEST(test_RTCtimer_Reset);

    UNITY_END();
    while(1){}
}

#endif
