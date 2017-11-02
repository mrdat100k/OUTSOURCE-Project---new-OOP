/******************************************************************************
 * @file    TestKeyboardController.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTKEYBOARDCONTROLLER_H_
#define TEST_TESTKEYBOARDCONTROLLER_H_
#include "KeyboardController.h"
#ifdef UNIT_TEST  // nếu định nghĩa UNIT_TEST thì thực hiện các lệnh dưới đây

class TestKeyboardController:public KeyboardController {
 public:
    TestKeyboardController(PinName _SELECT_PIN,
                           PinName _SET_PIN,
                           PinName _INVERTERON_PIN):
                           KeyboardController(_SELECT_PIN, _SET_PIN, _INVERTERON_PIN) {}

    int Getmenuindex(void);

    bool Gettimeron(void);

    void Setmenuindex(int);

    void TestAtTimeOut(void);

    void TestOnsetButtonLongPress(void);

    void TestOnSelectButtonPressFallIsr(void);

    void TestOnSetButtonPressFallIsr(void);

    void TestOnSetButtonPressRiseIsr(void);

    void TestOnInverterOnPressFallIsr(void);
};
#endif /*UNIT_TEST*/
#endif  // TEST_TESTKEYBOARDCONTROLLER_H_
