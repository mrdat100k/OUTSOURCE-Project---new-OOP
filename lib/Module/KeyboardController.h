/*!
 * \file var.h
 * \summary this
 *
 * \author
 *
 * \date October 2017
 *
 *
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <mbed.h>

class KeyboardController
{
public:
    uint8_t menu_index;
    bool timerOn;
    //************************************
    // Method:    KeyboardController::KeyboardController
    // Description:  KeyboardController constructor
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
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
    void attimeout();
    /*processing long press event on button*/
    void OnsetButtonLongPress();
    /*Processing when a falling edge pulse occur by pressing select button */
    void OnSelectButtonPress_fall_isr();
    /*Processing when a falling edge is occured by pressing set button*/
    void OnSetButtonPress_fall_isr();
    /*Processing when a rising edge is occured by pressing set button*/
    void OnSetButtonPress_rise_isr();
    /*Processing when a falling edge is occured by pressing inverter button*/
    void OnInverterOnPress_fall_isr();
};
    //************************************
    // Method:    KeyboardController::Init
    // Description:    initialization pressing button event
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::Init()
{
    select_button.fall(callback(this, &KeyboardController::OnSelectButtonPress_fall_isr));
    set_button.fall(callback(this, &KeyboardController::OnSetButtonPress_fall_isr));
    set_button.rise(callback(this, &KeyboardController::OnSetButtonPress_rise_isr));
}
    //************************************
    // Method:    KeyboardController::attimeout
    // Description:    skip to main menu when permissive time is out
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::attimeout()
{
    /*menu_index equal 0 when skip to main menu */
    menu_index = 0;
}
    //************************************
    // Method:    KeyboardController::OnSelectButtonPress_fall_isr
    // Description:    Processing when a falling edge pulse occur by pressing select button
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::OnSelectButtonPress_fall_isr()
{
    select_button.disable_irq();
    time_out.attach(callback(this, &KeyboardController::attimeout), 15);
    wait_ms(50);
    menu_index++;
    if (menu_index >= 3)
    {
        menu_index = 0;
    }

    select_button.enable_irq();
}
    //************************************
    // Method:    KeyboardController::OnSetButtonPress_fall_isr
    // Description:    Processing when a falling edge is occured by pressing set button
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::OnSetButtonPress_fall_isr()
{
    set_button.disable_irq();
    if(1 == menu_index || 2 == menu_index)
    {
        timerOn = !timerOn;
        time_out.attach(callback(this, &KeyboardController::OnsetButtonLongPress), 2);
    }
    set_button.enable_irq();
}
    //************************************
    // Method:    KeyboardController::OnSetButtonPress_rise_isr
    // Description:     Processing when a rising edge is occured by pressing set button
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::OnSetButtonPress_rise_isr()
{
    set_button.disable_irq();
    wait_ms(50);
    if(1 == menu_index || 2 == menu_index)
    {
        time_out.attach(callback(this, &KeyboardController::attimeout), 15);
    }
    set_button.enable_irq();
}
    //************************************
    // Method:    KeyboardController::OnsetButtonLongPress
    // Description:    Processing when time is out by long press event on button
    // Access:    private
    // Returns:
    // Qualifier:
    //***********************************
void KeyboardController::OnsetButtonLongPress()
{
    set_time(0);
}

#endif /*_KEYBOARD_H_*/
