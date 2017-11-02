/******************************************************************************
 * @file    TestRTC_Timer.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTRTC_TIMER_H_
#define TEST_TESTRTC_TIMER_H_
#include "RTCTimer.h"
#ifdef UNIT_TEST

class TestRTC_Timer: public RTC_Timer {
 public:
    TestRTC_Timer():RTC_Timer() {}
    uint32_t GetSecond_s(void);
};

#endif /*UNIT_TEST*/
#endif /*TEST_TESTRTC_TIMER_H_*/
