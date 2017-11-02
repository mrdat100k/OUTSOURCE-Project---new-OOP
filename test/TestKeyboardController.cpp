/******************************************************************************
 * @file    TestKeyboardController.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "TestKeyboardController.h"

#ifdef UNIT_TEST  // nếu định nghĩa UNIT_TEST thì  athực hiện các lệnh dưới đây

int  TestKeyboardController::Getmenuindex(void) {
    return menu_index;
}
bool TestKeyboardController::Gettimeron(void) {
    return timer_on;
}
void TestKeyboardController::Setmenuindex(int value) {
    menu_index = value;
}
void TestKeyboardController::TestAtTimeOut(void) {
    AtTimeOut();
}

void TestKeyboardController::TestOnsetButtonLongPress(void) {
    OnsetButtonLongPress();
}

void TestKeyboardController::TestOnSelectButtonPressFallIsr(void) {
    OnSelectButtonPressFallIsr();
}

void TestKeyboardController::TestOnSetButtonPressFallIsr(void) {
    OnSetButtonPressFallIsr();
}

void TestKeyboardController::TestOnSetButtonPressRiseIsr(void) {
    OnSetButtonPressRiseIsr();
}

void TestKeyboardController::TestOnInverterOnPressFallIsr(void) {
    OnInverterOnPressFallIsr();
}
#endif /*UNIT_TEST*/
