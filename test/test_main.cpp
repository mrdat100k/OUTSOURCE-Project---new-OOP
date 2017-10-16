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


void test_LCD_Batt(void)
{
    testlcdcontroller.SetBattVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattVolt(), 10);
    wait(0.1);
    testlcdcontroller.SetBattCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattCurr(), 30);
    wait(0.1);
    testlcdcontroller.SetBattPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattPower(), 30);
    wait(0.1);
    testlcdcontroller.SetBattEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattEnergy(), 30);
    wait(0.1);
}

void test_LCD_PV(void)
{
    testlcdcontroller.SetPVVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVVolt(), 10);
    wait(0.1);
    testlcdcontroller.SetPVCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVCurr(), 30);
    wait(0.1);
    testlcdcontroller.SetPVPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVPower(), 30);
    wait(0.1);
    testlcdcontroller.SetPVEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVEnergy(), 30);
    wait(0.1);
}

void test_LCD_Time(void)
{
    testlcdcontroller.SetTime(23,59,59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);
    wait(0.1);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);
    wait(0.1);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 23);
    wait(0.1);
}

void test_Keyboard_selectbutton(void)
{
    testkeyboard.AtTimeOut();
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 1);
    wait(0.1);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 2);
    wait(0.1);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 0);
    wait(0.1);
}

void test_Keyboard_setbutton(void)
{
    testkeyboard.AtTimeOut();
    testkeyboard.OnSelectButtonPressFallIsr();
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == true);
    wait(0.1);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == false);
    wait(0.1);
}

void test_INA(void)
{
    test_measurement.Calibrate(0.1, 3.2, 32);
    test_measurement.volt=32.1;
    test_measurement.curr=3.3;
    test_measurement.Scan();
    TEST_ASSERT(test_measurement.Get_voltage_out_of_range() == true);
    wait(0.1);
    TEST_ASSERT(test_measurement.Get_current_out_of_range() == true);
    wait(0.1);
    
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

    UNITY_END();
    while(1){}
}

#endif
