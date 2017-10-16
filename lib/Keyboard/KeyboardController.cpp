#include "mbed.h"
#include "KeyboardController.h"

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


int KeyboardController::Getmenuindex(void)
{
    return menu_index;
}

bool KeyboardController::Gettimeron(void)
{
    return timer_on;
}
