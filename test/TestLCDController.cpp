/******************************************************************************
 * @file    TestLCDController.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "TestLCDController.h"

#ifdef UNIT_TEST

float TestLCDController::GetBattVolt(void) {
    return battery_volt;
}

float TestLCDController::GetBattCurr(void) {
    return battery_curr;
}

float TestLCDController::GetBattPower(void) {
    return battery_power;
}

float TestLCDController::GetBattEnergy(void) {
    return battery_energy;
}

float TestLCDController::GetPVVolt(void) {
    return pv_volt;
}

float TestLCDController::GetPVCurr(void) {
    return pv_curr;
}

float TestLCDController::GetPVPower(void) {
    return pv_power;
}

float TestLCDController::GetPVEnergy(void) {
    return pv_energy;
}

int TestLCDController::GetTime(int i) {
    if (i == 0) {
            return second;
        }
    if (i == 1) {
            return minute;
        }
    if (i == 2) {
            return hour;
        }
}

#endif /*UNIT_TEST*/
