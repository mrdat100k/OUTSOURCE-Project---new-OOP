/******************************************************************************
 * @file    TestButton.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "TestButton.h"
#ifdef UNIT_TEST

void TestButton::TestSampleBTN(void) {
    if ((0 == button_curr_state)&&(0 == button_last_state)) {
        count++;
    } else {
        /*do nothing*/
    }
    if ((1 == button_curr_state)&&(0 == button_last_state)) {
        if (count < 150) {
            short_press = true;
        } else {
            long_press = true;
        }
        count = 0;
    } else {
        /*do nothong*/
    }
}

void TestButton::SetButtonLastState(bool value) {
    button_last_state = value;
}

void TestButton::SetButtonCurrentState(bool value) {
    button_curr_state = value;
}

void TestButton::SetCount(int value) {
    count = value;
}

int TestButton::GetCount(void) {
    return count;
}
#endif /*UNIT_TEST*/
