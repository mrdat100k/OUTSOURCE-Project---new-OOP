#include <mbed.h>
#include <var.h>
#include <LCDController.h>
#include <INAReader.h>
#include <RTCTimer.h>
#include <KeyboardController.h>
LCDController test(&g_lcd_object);
INAReader ina_reader(&g_battery_measure_object, &g_pv_measure_object);
KeyboardController keyboard(&g_select_button, &g_set_button, &g_inverter_on);
int main() {
  wait(2);

    // put your setup code here, to run once:
//lcdcontroller.showLogo(watershed_logo_data);
test.showLogo();
wait(5);
    while(1) {
        // put your main code here, to run repeatedly:
        test.updateScreen(g_menu_index);
    }
}
