#include "../inc/smart_bin.h"

static volatile int8_t keep_scanning;

void motion_sensor_tracker()
{
        keep_scanning = 1;
        while(keep_scanning) {
                if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
                        PRINT_DEBUG("Motion detected.");
                        wait_for_selection();
                        keep_scanning = 0;
                }

                delay(1000);
        }
}

void wait_for_selection()
{

}
