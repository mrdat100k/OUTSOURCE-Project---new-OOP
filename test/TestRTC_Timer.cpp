/******************************************************************************
 * @file    TestRTC_Timer.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "TestRTC_Timer.h"
#ifdef UNIT_TEST

uint32_t TestRTC_Timer::GetSecond_s() {
    return time(NULL);
}

#endif /*UNIT_TEST*/
