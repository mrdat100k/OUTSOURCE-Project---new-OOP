/******************************************************************************
 * @file    TestINAReader.h
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef TEST_TESTINAREADER_H_
#define TEST_TESTINAREADER_H_

#include "INAReader.h"
#ifdef UNIT_TEST

class TestINAReader: public INAReader {
 public:
    TestINAReader(PinName sda, PinName scl,
                  int addr = 0x40,
                  int freq = 100000,
                  resolution_t res = RES_12BITS):
                  INAReader(sda, scl, 0x40, 100000, RES_12BITS) {}
    bool Get_voltage_out_of_range();
    bool Get_current_out_of_range();
    void SetVolt(float value);
    void SetCurr(float value);
    void SetPower(float value);
    void TestScanning();
};

#endif /*UNIT_TEST*/
#endif /*TEST_TESTINAREADER_H_*/
