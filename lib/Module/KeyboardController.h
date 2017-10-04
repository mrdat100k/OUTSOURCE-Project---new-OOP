#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <var.h>
static void attimeout();
static void OnSelectButtonPress_fall_isr();
static void OnSetButtonPress_fall_isr();
static void OnSetButtonPress_rise_isr();
static void OnInverterOnPress_fall_isr();
class KeyboardController
{
public:
    KeyboardController(InterruptIn* _select_button_ptr, InterruptIn* _set_button_ptr, InterruptIn* _inverter_on_ptr)
    {
        select_button_ptr = _set_button_ptr;
        set_button_ptr = _set_button_ptr;
        inverter_on_ptr = _inverter_on_ptr;
        Init();
    }
private:
    InterruptIn* select_button_ptr;
    InterruptIn* set_button_ptr;
    InterruptIn* inverter_on_ptr;
    void Init();
};
void KeyboardController::Init()
{
    select_button_ptr -> fall(&OnSelectButtonPress_fall_isr);
}
void attimeout()
{
    g_menu_index = 0;
}
void OnSelectButtonPress_fall_isr()
{
    g_select_button.disable_irq();
    g_timeout.attach(&attimeout, 15);
    wait_ms(20);
    g_menu_index++;
    if (g_menu_index >= 3)
    {
    		g_menu_index = 0;
    }

    g_select_button.enable_irq();
}
#endif /*_KEYBOARD_H_*/
