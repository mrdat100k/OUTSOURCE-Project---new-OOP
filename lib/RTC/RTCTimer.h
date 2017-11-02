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
#ifndef LIB_RTC_RTCTIMER_H_
#define LIB_RTC_RTCTIMER_H_
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
    RTC_Timer() {
        timer_state = false;
        second = 0;
        minute = 0;
        hour = 0;
        day = 0;
        set_time(0);
    }
    void Reset(void);
    void Off(void);
    void On(void);
    void ChangeState(void);
    bool GetState(void);
    void Update(void);
    int GetSecond(void);
    int GetMinute(void);
    int GetHour(void);
    uint32_t GetSecond_s(void);

 protected:
    bool timer_state;
    uint8_t second, minute, hour, day;
    uint32_t seconds;
};
#endif /*LIB_RTC_RTCTIMER_H_*/

class TestRTC_Timer: public RTC_Timer {
 public:
   TestRTC_Timer():RTC_Timer(){}
};
