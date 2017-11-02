/******************************************************************************
 * @file    EventHandling.cpp
 * @author   Dua Nguyen
 * @brief
 * @date     Nov. 2017
 * @date modified 2017/11/2
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *****************************************************************************/
#include "mbed.h"
#include "EventHandling.h"
/************************************
 * Method:  EventHandling::EventHandling
 * @brief: EventHandling constructor
 * Access: public
 * Returns:
 * Qualifier:
 * @TODO <nothing>
***********************************/
EventHandling::EventHandling() {
    menu_index = 0;
    timer_is_on = true;
    timer_reset = false;
    inverter_turn_on = false;
}
/** @brief: Getter menu_index
 *  @return: 0 - main menu display, 1 - second menu display, 2 - third menu display.
 */
int EventHandling::GetMenuIndex() {
    return menu_index;
}
/** @brief: Getter timer_is_on
 *  @return: true - turn on timer, false - turn off timer.
 */
bool EventHandling::GetTimerIsOn() {
    return timer_is_on;
}
/** @brief: Getter timer_reset
 *  @return: true - reset timer, false - do nothing.
 */
bool EventHandling::GetTimerReset() {
    bool return_value = timer_reset;
    timer_reset = false;
    return return_value;
}
/** @brief: Getter short_press
 *  @return: true - turns on digital output for AC/DC inverter.
 */
bool EventHandling::GetInverterTurnOn() {
    return inverter_turn_on;
}
/** @brief: Thay đổi trạng thái màn hình menu_index
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
void EventHandling::SwitchMenuTrigger(bool trigger) {
    if (true == trigger) {
        menu_index++;
        time_out.attach(callback(this, &EventHandling::TimeoutCallback), TIMEOUT_PERIOD);
    } else {
      /* do nothong */
    }
    if (3 == menu_index) {
        menu_index = 0;
    } else {
      /* do nothing */
    }
}
/** @brief: Thay đổi trạng thái biến timer_is_on
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
void EventHandling::TimerIsOnTrigger(bool trigger) {
    if ((true == trigger)&&(menu_index != 0)) {
        timer_is_on = !timer_is_on;
        time_out.attach(callback(this, &EventHandling::TimeoutCallback), TIMEOUT_PERIOD);
    } else {
      /* do nothing */
    }
}
/** @brief: Thay đổi trạng thái biến timer_reset
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
void EventHandling::TimerResetTrigger(bool trigger) {
    if ((true == trigger)&&(menu_index != 0)) {
        timer_reset = true;
        time_out.attach(callback(this, &EventHandling::TimeoutCallback), TIMEOUT_PERIOD);
    } else {
      /* do nothing */
    }
}
/** @brief: Thay đổi trạng thái biến inverter_turn_on
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
void EventHandling::InverterTurnOnTrigger(bool trigger) {
    if (true == trigger) {
        inverter_turn_on = !inverter_turn_on;
        time_out.attach(callback(this, &EventHandling::TimeoutCallback), TIMEOUT_PERIOD);
    } else {
      /* do nothing */
    }
}
/** @brief: Hàm này sẽ được gọi khi time out
 */
void EventHandling::TimeoutCallback() {
    menu_index = 0;
}
