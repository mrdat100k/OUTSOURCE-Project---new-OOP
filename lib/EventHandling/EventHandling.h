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
 *  A class handles các sự kiện xuất hiện trong quá trình hệ thống hoạt động
 * như một nút nhấn được bấm, các sự cố quá dòng, quá áp, các exception xảy ra
 * trong quá trình hoạt động nhằm thay đổi trạng thái hệ thống tương ứng với
 * từng sự kiện.
 * Example:
 * @code

 * @endcode
 */
class EventHandling {
private:
    int menu_index;            /**< Chỉ màn hình nào sẽ được hiển thị */
    bool timer_is_on;          /**< true khi bật timer, false khi tắt timer */
    bool timer_reset;          /**< timer sẽ bị reset về 0 khi biến này là true */
    bool inverter_turn_on;     /**< turns on digital output for AC/DC inverter */
    Timeout time_out;
/** @brief: Hàm này sẽ được gọi khi time out
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
/** @brief: Thay đổi trạng thái màn hình menu_index
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
    void SwitchMenuTrigger(bool trigger);
/** @brief: Thay đổi trạng thái biến timer_is_on
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
    void TimerIsOnTrigger(bool trigger);
/** @brief: Thay đổi trạng thái biến timer_reset
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
    void TimerResetTrigger(bool trigger);
/** @brief: Thay đổi trạng thái biến inverter_turn_on
 *  @param: trigger tác nhân thay đổi trạng thái.
 */
    void InverterTurnOnTrigger(bool trigger);

  };
 #endif /*LIB_EVENTHANDLING_EVENTHANDLING_H_*/
