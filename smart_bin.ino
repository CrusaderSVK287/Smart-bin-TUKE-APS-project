#include <Arduino.h>
#include "inc/smart_bin.h"

void setup()
{
        Serial.begin(SERIAL_PORT);
        Serial.println("STARTING SERIAL COMMUNICATION ON 9600");

        pinMode(MOTION_SENSOR_PIN, INPUT);
}

void loop()
{
        motion_sensor_tracker();
}
