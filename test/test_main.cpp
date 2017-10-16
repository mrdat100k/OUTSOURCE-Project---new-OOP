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
void DisplayLCD_WhenChangingBatteryParameters_ChangingParametersToDisplay(void)
{
    /* All of these should pass */
    testlcdcontroller.SetBattVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattVolt(), 10);
    testlcdcontroller.SetBattCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattCurr(), 30);
    testlcdcontroller.SetBattPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattPower(), 30);
    testlcdcontroller.SetBattEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetBattEnergy(), 30);
}

void DisplayLCD_WhenChangingPVParameters_ChangingParametersToDisplay(void)
{
    /* All of these should pass */
    testlcdcontroller.SetPVVolt(10);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVVolt(), 10);
    testlcdcontroller.SetPVCurr(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVCurr(), 30);
    testlcdcontroller.SetPVPower(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVPower(), 30);
    testlcdcontroller.SetPVEnergy(30);
    TEST_ASSERT_EQUAL_FLOAT(testlcdcontroller.GetPVEnergy(), 30);
}

void DisplayLCD_WhenChangingTimerParameters_ChangingParametersToDisplay(void)
{   /* All of these should pass */
    testlcdcontroller.SetTime(23,59,59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(0), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(1), 59);
    TEST_ASSERT_EQUAL_INT8(testlcdcontroller.GetTime(2), 23);
}

void PressingKeyboard_WhenMenuButtonIsPressed_ChangingMenuParameter(void)
{   /* All of these should pass */
    testkeyboard.AtTimeOut();
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 1);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 2);
    testkeyboard.OnSelectButtonPressFallIsr();
    TEST_ASSERT_EQUAL_INT8(testkeyboard.Getmenuindex(), 0);
}

void PressingKeyboard_WhenChangingTimerStateButtonIsPressed_ChangingTimerParameters(void)
{   /* All of these should pass */
    testkeyboard.Setmenuindex(1);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == true);
    testkeyboard.Setmenuindex(2);
    testkeyboard.OnSetButtonPressFallIsr();
    TEST_ASSERT(testkeyboard.Gettimeron() == false);
}
void MethodsOfINA_WhenCallingMethods_CheckingInputValues(void)
{   /* All of these should pass */
    test_measurement.Calibrate(0.1, 3.2, 32);
    test_measurement.GetVolt(32.1);
    test_measurement.GetCurr(3.3);
    test_measurement.TestScanning();
    TEST_ASSERT(test_measurement.Get_voltage_out_of_range() == true);
    TEST_ASSERT(test_measurement.Get_current_out_of_range() == true);
}

void ResetRTCtimer_WhenResetTimer_ResetTimerValues(void)
{
    /* All of these should pass */
    test_rtctimer.Reset();
    TEST_ASSERT(test_rtctimer.GetState() == true);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetSecond(), 0);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetMinute(), 0);
    TEST_ASSERT_EQUAL_INT8(test_rtctimer.GetHour(), 0);


}

void StateTimer_WhenChangingTimerState_ChangingtimerState(void)
{
    test_rtctimer.On();
    TEST_ASSERT(test_rtctimer.GetState() == true);
    test_rtctimer.Off();
    TEST_ASSERT(test_rtctimer.GetState() == false);
    test_rtctimer.ChangeState();
    TEST_ASSERT(test_rtctimer.GetState() == true);
}

void UpdateRTCtimer_WhenUpdatingTimerValues_ChaningTimerValues(void)
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

    RUN_TEST(DisplayLCD_WhenChangingBatteryParameters_ChangingParametersToDisplay);

    RUN_TEST(DisplayLCD_WhenChangingPVParameters_ChangingParametersToDisplay);

    RUN_TEST(DisplayLCD_WhenChangingTimerParameters_ChangingParametersToDisplay);

    RUN_TEST(PressingKeyboard_WhenMenuButtonIsPressed_ChangingMenuParameter);

    RUN_TEST(PressingKeyboard_WhenChangingTimerStateButtonIsPressed_ChangingTimerParameters);

    RUN_TEST(MethodsOfINA_WhenCallingMethods_CheckingInputValues);

    RUN_TEST(ResetRTCtimer_WhenResetTimer_ResetTimerValues);

    RUN_TEST(RUN_TEST(StateTimer_WhenChangingTimerState_ChangingtimerState);

    RUN_TEST(UpdateRTCtimer_WhenUpdatingTimerValues_ChaningTimerValues);

    UNITY_END();
    while(1){}
}

#endif
