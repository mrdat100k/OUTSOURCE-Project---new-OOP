 /******************************************************************************
  * @file    KeyboardController.h
  * @author Dua Nguyen
  * @brief
  * @date     Oct. 2017
  * @date modified 2017/10/13
  * @version 1.0.0
  * Copyright(C) 2017
  * All rights reserved.
  *
  *****************************************************************************/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <mbed.h>
/* Class content lcd display UI
 * If this source file built with example, the <KeyboardController.h> library
 * must be included
 */
/*
 * Example:
 * @code
 * TODO: updating
 * @endcode
 * @ingroup module
 */
class KeyboardController
{
public:
   /* @param menu_index choosing menu screen
    * @param timer_on timer state
    */
    uint8_t menu_index;
    bool timer_on;
    /************************************
    * Method:  KeyboardController::KeyboardController
    * @brief: KeyboardController constructor
    * @param _SELECT_PIN input pin of menu selecting button
    * @param _SET_PIN input pin of setting button
    * @param _INVERTERON_PIN input pin for inverter mode
    * Access: public
    * Returns:
    * Qualifier:
    * Exceptions: 1. When keyboard is not connected 
    * @TODO <nothing>
    ***********************************/
    KeyboardController(PinName _SELECT_PIN, PinName _SET_PIN, PinName _INVERTERON_PIN):
    select_button(_SELECT_PIN),
    set_button(_SET_PIN),
    inverter_on(_INVERTERON_PIN)
    {
        Init();
    }
private:
    InterruptIn select_button;
    InterruptIn set_button;
    InterruptIn inverter_on;
    Timeout time_out;
    /*initialization pressing button event */
    void Init();
    /*skip to main menu when permissive time is out*/
    void AtTimeOut();
    /*processing long press event on button*/
    void OnsetButtonLongPress();
    /*Processing when a falling edge pulse occur by pressing select button */
    void OnSelectButtonPressFallIsr();
    /*Processing when a falling edge is occured by pressing set button*/
    void OnSetButtonPressFallIsr();
    /*Processing when a rising edge is occured by pressing set button*/
    void OnSetButtonPressRiseIsr();
    /*Processing when a falling edge is occured by pressing inverter button*/
    void OnInverterOnPressFallIsr();
};
   /************************************
    * Method: KeyboardController::Init
    * Description: initialization pressing button event
    * Access: private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::Init()
{
    select_button.fall(callback(this, &KeyboardController::OnSelectButtonPressFallIsr));
    set_button.fall(callback(this, &KeyboardController::OnSetButtonPressFallIsr));
    set_button.rise(callback(this, &KeyboardController::OnSetButtonPressRiseIsr));
}
   /************************************
    * Method: KeyboardController::AtTimeOut
    * Description: skip to main menu when permissive time is out
    * Access: private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::AtTimeOut()
{
    /*menu_index equal 0 when skip to main menu */
    menu_index = 0;
}
   /************************************
    * Method:    KeyboardController::OnSelectButtonPressFallIsr
    * Description:    Processing when a falling edge pulse occur by pressing select button
    * Access:    private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::OnSelectButtonPressFallIsr()
{
    select_button.disable_irq();
    time_out.attach(callback(this, &KeyboardController::AtTimeOut), 15);
    wait_ms(50);
    menu_index++;
    if (menu_index >= 3)
    {
        menu_index = 0;
    }
    else
    {
        /*Do nothing*/
    }

    select_button.enable_irq();
}
   /************************************
    * Method: KeyboardController::OnSetButtonPressFallIsr
    * Description: Processing when a falling edge is occured by pressing set button
    * Access: private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::OnSetButtonPressFallIsr()
{
    set_button.disable_irq();
    if((1 == menu_index) || (2 == menu_index))
    {
        timer_on = !timer_on;
        time_out.attach(callback(this, &KeyboardController::OnsetButtonLongPress), 2);
    }
    else
    {
        /*Do nothing*/
    }
    set_button.enable_irq();
}
   /************************************
    * Method: KeyboardController::OnSetButtonPressRiseIsr
    * Description: Processing when a rising edge is occured by pressing set button
    * Access: private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::OnSetButtonPressRiseIsr()
{
    set_button.disable_irq();
    wait_ms(50);
    if((1 == menu_index) || (2 == menu_index))
    {
        time_out.attach(callback(this, &KeyboardController::AtTimeOut), 15);
    }
    else
    {
        /*Do nothing*/
    }
    set_button.enable_irq();
}
   /************************************
    * Method: KeyboardController::OnsetButtonLongPress
    * Description: Processing when time is out by long press event on button
    * Access: private
    * Returns:
    * Qualifier:
    ***********************************/
void KeyboardController::OnsetButtonLongPress()
{
    set_time(0);
}

#endif /*_KEYBOARD_H_*/
