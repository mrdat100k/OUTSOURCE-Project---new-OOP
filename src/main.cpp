/*! file chứa chương trình chính
* chương trình demo: đọc giá trị cảm biến, cập nhật thời gian,
* hiển thị ra màn hình lcd, nút nhấn để chuyển menu, reset thời gian.
*
*/
#include <mbed.h>
#include <var.h>
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
/*khởi tạo đối tượng lcdcontroller*/
LCDController lcdcontroller(&g_lcd_object);
/*khởi tạo đối tượng đo lường*/
INAReader ina_reader(&g_battery_measure_object, &g_pv_measure_object);
/*khởi tạo đối tượng bàn phím*/
KeyboardController keyboard(SELECT_BUTTON_PIN, SET_BUTTON_PIN, INVERTER_ON_PIN);
/*khởi tạo đối tượng đồng hồ thời gian thực*/
RTC_Timer rtc_timer;
int main() {

    // put your setup code here, to run once:
	/*hiển thị logo watershed ra màn hình*/
    lcdcontroller.showLogo();
    wait(3);
    while(1) {
        // put your main code here, to run repeatedly:
		/*quét giá trị đo được từ cảm biến*/
        ina_reader.Scan();
		/*cập nhật thời gian thực*/
        rtc_timer.Update();
		/*truyền vào đối tượng màn hình các thông số cần hiển thị*/
        lcdcontroller.setBattVolt(ina_reader.getBattVolt());
        lcdcontroller.setBattCurr(ina_reader.getBattCurr());
        lcdcontroller.setBattPower(ina_reader.getBattPower());
        lcdcontroller.setPVVolt(ina_reader.getPVVolt());
        lcdcontroller.setPVCurr(ina_reader.getPVCurr());
        lcdcontroller.setPVPower(ina_reader.getPVPower());
        lcdcontroller.setTime(rtc_timer.GetHour(), rtc_timer.GetMinute(), rtc_timer.GetSecond());
		/*Cập nhật giá trị ra màn hình, màn hình được điều khiển bằng nút nhấn*/
        lcdcontroller.updateScreen(keyboard.menu_index);
    }
}
