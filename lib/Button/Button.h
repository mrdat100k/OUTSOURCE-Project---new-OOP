/******************************************************************************
 * @file    Button.h
 * @author   Dua Nguyen
 * @brief    button handling library
 * @date     Oct. 2017
 * @date modified 2017/10/27
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef  LIB_BUTTON_BUTTON_H_
#define LIB_BUTTON_BUTTON_H_
#include "mbed.h"
#define BTN_SAMPLING_PERIOD 0.01
/** Class: Button
 *  A class handles button input procedure, which uses DigitalIn and Ticker
 * Example:
 * @code
 * // Button sample
 * #include "mbed.h"
 * #include "Button.h"
 * #define button_pin PB_1
 * #define led_pin PA_0
 * Button btn(button_pin);
 * DigitalOut test_led(led_pin);
 * int main()
 * {
 *     while(true) {
 *         if(btn.GetShortPress()) {
 *             test_led = 1;
 *         } else {
 *             //do nothing
 *         }
 *         if(btn.GetLongPress()) {
 *             test_led = 0;
 *         } else {
 *             //do nothing
 *         }
 *
 *     }
 * }
 * @endcode
 */
class Button : public DigitalIn {
private:
/** SampleBTN input and process */
    void SampleBTN();
    Ticker _tick;
    bool short_press;    /*!< short_press represents that the button has been short pressed.
                          *   @retval true - button has been short pressed
                          */
    bool long_press;    /*!< long_press represents that the button has been long pressed.
                          *  @retval true - button has been long pressed
                          */
    int button_last_state;
    int count;
    int button_curr_state;

public:
/** constructor
 *
 *  @param pin - button pin number (DigitalIn), the pin is PullUp internally
 */
    Button(PinName pin);
/** @brief: Getter short_press
 *  @return: true when button has been short pressed.
 */
    bool GetShortPress();
/** @brief: Getter long_press
 *  @return: true when button has been long pressed.
 */
    bool GetLongPress();
/** @brief: Get button status
 *  @return: true when button is being pressed.
 */
    bool GetButtonState();
};
#endif /*LIB_BUTTON_BUTTON_H_*/
