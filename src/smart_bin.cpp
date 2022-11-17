#include "../inc/smart_bin.h"
#include "../inc/lcd_wrapper.h"

void motion_sensor_tracker()
{
        while(1) {
                if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
                        PRINT_DEBUG("Motion detected.");
                        wait_for_selection();
                        break;
                }

                delay(1000);
        }
}

void wait_for_selection()
{

}
