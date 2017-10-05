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
    /*Constructor*/
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
<<<<<<< HEAD
	/*Khởi tạo các sự kiện ngắt cho nút nhấn*/
    void Init();
	/*Hàm chuyển về menu chính khi timeout*/
=======
    /*
    khởi tạo các sự kiện trong ngắt
    */
    void Init();
    /*
    hàm chuyển màn hình
    */
>>>>>>> d0462c14f9039c6e9bfa754c894ef2ebecdd70bf
    void attimeout();
	/*Hàm phục vụ sự kiện nhấn giữ nút set*/
    void OnsetButtonLongPress();
	/*Hàm phục vụ ngắt sườn xuống nút nhấn select*/
    void OnSelectButtonPress_fall_isr();
	/*Hàm phục vụ ngắt sườn xuống nút nhấn set*/
    void OnSetButtonPress_fall_isr();
	/*Hàm phục vụ ngắt sườn lên nút nhấn set*/
    void OnSetButtonPress_rise_isr();
	/*Hàm phục vụ ngắt sườn xuống nút nhấn điều khiển inverter*/
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
	/*Gán chỉ số menu bằng 0 để trở về menu chính*/
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
