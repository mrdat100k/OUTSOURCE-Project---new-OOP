/******************************************************************************
 * @file    TestButton.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTBUTTON_H_
#define TEST_TESTBUTTON_H_
#include "Button.h"
#ifdef UNIT_TEST
class TestButton : public Button {
 public:
    explicit TestButton(PinName pin): Button(pin) {}

    void TestSampleBTN();

    void SetButtonLastState(bool value);

    void SetButtonCurrentState(bool value);

    void SetCount(int value);

    int GetCount(void);
};
#endif /*UNIT_TEST*/
#endif /*TEST_TESTBUTTON_H_*/
