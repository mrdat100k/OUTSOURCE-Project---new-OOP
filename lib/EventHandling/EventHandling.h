/******************************************************************************
 * @file    EventHandling.h
 * @author   Dua Nguyen
 * @brief
 * @date     Nov. 2017
 * @date modified 2017/11/2
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef LIB_EVENTHANDLING_EVENTHANDLING_H_
#define LIB_EVENTHANDLING_EVENTHANDLING_H_
#include "mbed.h"
#define TIMEOUT_PERIOD 15
/** Class: EventHandling
 *  A class handles all actor of system
 * Example:
 * @code
 * @TODO: update
 * @endcode
 */
class EventHandling {
protected:
    int menu_index;            /**< screen selected */
    bool timer_is_on;          /**< true is turn on timer, false is turn of timer */
    bool timer_reset;          /**< timer will be reset if this varible is true */
    bool inverter_turn_on;     /**< turns on digital output for AC/DC inverter */
    Timeout time_out;
/** @brief: This function will be call when time out
 */
    void TimeoutCallback();
public:
/************************************
 * Method:  EventHandling::EventHandling
 * @brief: EventHandling constructor
 * Access: public
 * Returns:
 * Qualifier:
 * @TODO <nothing>
***********************************/
    EventHandling();
/** @brief: Getter menu_index
 *  @return: 0 - main menu display, 1 - second menu display, 2 - third menu display.
 */
    int GetMenuIndex();
/** @brief: Getter timer_is_on
 *  @return: true - turn on timer, false - turn off timer.
 */
    bool GetTimerIsOn();
/** @brief: Getter timer_reset
 *  @return: true - reset timer, false - do nothing.
 */
    bool GetTimerReset();
/** @brief: Getter short_press
 *  @return: true - turns on digital output for AC/DC inverter.
 */
    bool GetInverterTurnOn();
/** @brief: Read input actor for menu_index
 *  @param: trigger - input actor switch screen.
 */
    void SwitchMenuTrigger(bool trigger);
/** @brief: Read input actor for timer_is_on
 *  @param: trigger - input actor change timer status.
 */
    void TimerIsOnTrigger(bool trigger);
/** @brief: Read input actor for timer_reset
 *  @param: trigger - input actor reset timer.
 */
    void TimerResetTrigger(bool trigger);
/** @brief: Read input actor for inverter_turn_on
 *  @param: trigger - input actor turn on/off inverter.
 */
    void InverterTurnOnTrigger(bool trigger);

  };
 #endif /*LIB_EVENTHANDLING_EVENTHANDLING_H_*/
