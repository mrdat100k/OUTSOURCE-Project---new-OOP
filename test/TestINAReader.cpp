/******************************************************************************
 * @file    TestINAReader.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "TestINAReader.h"
#ifdef UNIT_TEST

bool TestINAReader::Get_voltage_out_of_range() {
    return voltage_out_of_range;
}
bool TestINAReader::Get_current_out_of_range() {
    return current_out_of_range;
}
void TestINAReader::SetVolt(float value) {
    volt = value;
}
void TestINAReader::SetCurr(float value) {
    curr = value;
}
void TestINAReader::SetPower(float value) {
    power = value;
}
void TestINAReader::TestScanning() {
    if ( volt >= max_voltage ) {
        voltage_out_of_range = true;
    } else {
        voltage_out_of_range = false;
    }
    if ( curr >= max_current ) {
        current_out_of_range = true;
    } else {
        current_out_of_range = false;
    }
}

#endif /*UNIT_TEST*/
