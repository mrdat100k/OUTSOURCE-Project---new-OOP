/******************************************************************************
 * @file    TestLCDController.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTLCDCONTROLLER_H_
#define TEST_TESTLCDCONTROLLER_H_

#include "LCDController.h"
#ifdef UNIT_TEST

class TestLCDController: public LCDController {
 public:
      TestLCDController(I2C &i2c,
                        PinName RST = NC,
                        uint8_t rawHeight = 64,
                        uint8_t rawWidth = 128):
                        LCDController(i2c, NC, 64, 128) {}
    float GetPVVolt(void);

    float GetPVCurr(void);

    float GetPVPower(void);

    float GetPVEnergy(void);

    float GetBattVolt(void);

    float GetBattCurr(void);

    float GetBattPower(void);

    float GetBattEnergy(void);

    int GetTime(int);
};

#endif /*UNIT_TEST*/
#endif /*TEST_TESTLCDCONTROLLER_H_*/
