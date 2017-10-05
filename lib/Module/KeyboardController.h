/*!
 * \file var.h
 * \summary file lớp đối tượng phím ấn
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
    /*Constructer*/
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

    void Init();
    void attimeout();
    void OnsetButtonLongPress();
    void OnSelectButtonPress_fall_isr();
    void OnSetButtonPress_fall_isr();
    void OnSetButtonPress_rise_isr();
    void OnInverterOnPress_fall_isr();
};
void KeyboardController::Init()
{
    select_button.fall(callback(this, &KeyboardController::OnSelectButtonPress_fall_isr));
    set_button.fall(callback(this, &KeyboardController::OnSetButtonPress_fall_isr));
    set_button.rise(callback(this, &KeyboardController::OnSetButtonPress_rise_isr));
}
void KeyboardController::attimeout()
{
    menu_index = 0;
}
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
void KeyboardController::OnsetButtonLongPress()
{
    set_time(0);
}

#endif /*_KEYBOARD_H_*/
