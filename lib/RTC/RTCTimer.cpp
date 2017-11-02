/******************************************************************************
 * @file    RTC_Timer.cpp
 * @author  Dua Nguyen
 * @brief    this file consist of realtime clock classes
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version   1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "RTCTimer.h"

/************************************
* Method: RTC_Timer::Reset
* Description: reset time value
* Access: public
* Returns:
* Qualifier:
************************************/
void RTC_Timer::Reset() {
    timer_state = true;
    set_time(0);
    second = 0;
    minute = 0;
    hour = 0;
    day = 0;
}
void RTC_Timer::Off() {
    timer_state = false;
}
void RTC_Timer::On() {
    timer_state = true;
}
void RTC_Timer::ChangeState() {
    timer_state = !timer_state;
}
bool RTC_Timer::GetState() {
    return timer_state;
}
/************************************
* Method: RTC_Timer::Update
* Description: Updating second value, minute value, hour value
* Access: public
* Returns:
* Qualifier:
************************************/
void RTC_Timer::Update() {
    /* Update timer*/
    seconds = time(NULL); /*TODO: bo sung header cho ham time */
    second = seconds % 60;
    minute = seconds % 3600 / 60;
    hour = seconds % 86400 / 3600;
}

int RTC_Timer::GetSecond() {
    return second;
}

int RTC_Timer::GetMinute() {
    return minute;
}

int RTC_Timer::GetHour() {
    return hour;
}
