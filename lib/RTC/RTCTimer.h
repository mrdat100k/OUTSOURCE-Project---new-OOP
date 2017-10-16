/******************************************************************************
 * @file    INAReader.h
 * @author  Dua Nguyen
 * @brief    this file consist of realtime clock classes
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version   1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef _RTCTIMER_H_
#define _RTCTIMER_H_
#include <mbed.h>
/* Class for configuration and Reading data from INA module
* If this source file built with example, the <RTCTimer.h> library
* must be included
*/
/*
* Example:
* @code
* TODO: updating
* @endcode
* @ingroup module
*/
class RTC_Timer{
public:
    /************************************
    * Method: RTC_Timer::RTC_Timer
    * Description: RTC_Timer constructor
    * Access: public
    * Returns:
    * Qualifier:
    ************************************/
    RTC_Timer()
    {
        timer_state = false;
        second = 0;
        minute = 0;
        hour = 0;
        day = 0;
        set_time(0);
    }
    /************************************
    * Method: RTC_Timer::Reset
    * Description: reset time value
    * Access: public
    * Returns:
    * Qualifier:
    ************************************/
    void Reset()
    {
        timer_state = true;
        set_time(0);
        second = 0;
        minute = 0;
        hour = 0;
        day = 0;
    }
    void Off()
    {
        timer_state = false;
    }
    void On()
    {
        timer_state = true;
    }
    void ChangeState()
    {
        timer_state = !timer_state;
    }
    bool GetState()
    {
        return timer_state;
    }
    /************************************
    * Method: RTC_Timer::Update
    * Description: Updating second value, minute value, hour value
    * Access: public
    * Returns:
    * Qualifier:
    ************************************/
    void Update()
    {
        /* Update timer*/
        seconds = time(NULL); /*TODO: bo sung header cho ham time */
        second = seconds % 60;
        minute = seconds % 3600 / 60;
        hour = seconds % 86400 / 3600;
    }

    int GetSecond()
    {
        return second;
    }

    int GetMinute()
    {
        return minute;
    }

    int GetHour()
    {
        return hour;
    }

    uint32_t GetSecond_s()
    {
        return time(NULL);
    }

private:
    bool timer_state;
    uint8_t second, minute, hour, day;
    uint32_t seconds;

};
#endif /*_RTCTIMER_H_*/
