/******************************************************************************
 * @file    Button.cpp
 * @author   Dua Nguyen
 * @brief    button handling library
 * @date     Oct. 2017
 * @date modified 2017/10/27
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "Button.h"
#include "mbed.h"

// constructor
/** Create a Button object connected to a DigtalIn pin
 *
 * @param pin - DigitalIn pin connected to the switch
 */
Button::Button(PinName pin) : DigitalIn(pin) {
    mode(PullUp);
    short_press = false;
    long_press = false;
    _tick.attach(callback(this, &Button::SampleBTN), BTN_SAMPLING_PERIOD);
}
// private function
/** SampleBTN input and process */
void Button::SampleBTN() {
    int button_last_state;
    static int count = 0;
    static int button_curr_state = 1;
    button_last_state = button_curr_state;
    button_curr_state = read();
    if ((0 == button_curr_state)&&(0 == button_last_state)) {
        count++;
    } else {
        /*do nothing*/
    }
    if ((1 == button_curr_state)&&(0 == button_last_state)) {
        if(count < 150) {
            short_press = true;
        } else {
            long_press = true;
        }
        count = 0;
    } else {
        /*do nothong*/
    }
}
// public function
/************************************
* Method:    Button::GetShortPress
* Description:    Get the event that the button has been short pressed.
* Access:    public
* Returns:   true - button has been short pressed.
* Qualifier:
***********************************/
bool Button::GetShortPress() {
    bool return_value;
    return_value = short_press;
    short_press = false;
    return return_value;
}
/************************************
* Method:    Button::GetLongPress
* Description:    Get the event that the button has been long pressed.
* Access:    public
* Returns:   true - button has been long pressed.
* Qualifier:
***********************************/
bool Button::GetLongPress() {
    bool return_value;
    return_value = long_press;
    long_press = false;
    return return_value;
}
/************************************
* Method:    Button::GetButtonState
* Description:    Get the event that the button is being pressed.
* Access:    public
* Returns:   true - button is being pressed.
* Qualifier:
***********************************/
bool Button::GetButtonState() {
    bool return_value;
    if(1 == read()) {
        return_value = false;
    } else {
        return_value = true;
    }
    return return_value;
}
