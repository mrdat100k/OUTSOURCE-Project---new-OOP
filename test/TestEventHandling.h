/******************************************************************************
 * @file    TestEventHandling.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTEVENTHANDLING_H_
#define TEST_TESTEVENTHANDLING_H_
#include "EventHandling.h"
#ifdef UNIT_TEST

class TestEventHandling: public EventHandling {
 public:
    TestEventHandling():EventHandling(){}

    void TestTimeoutCallback();
};

#endif /*UNIT_TEST*/
#endif /*TEST_TESTEVENTHANDLING_H_*/
