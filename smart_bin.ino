#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "inc/lcd_wrapper.h"
#include "inc/smart_bin.h"

void setup()
{
        /* Initialise lcd display */
        lcd_init();

        /* Initialise serial communication for debug messages */
        Serial.begin(SERIAL_PORT);
        Serial.println("STARTING SERIAL COMMUNICATION ON 9600");

        /* Initialise pins */
        pinMode(MOTION_SENSOR_PIN, INPUT);

        pinMode(PIN_BTN_1, INPUT);
        pinMode(PIN_BTN_2, INPUT);
        pinMode(PIN_BTN_3, INPUT);
        pinMode(PIN_BTN_4, INPUT);

        pinMode(PIN_SIGNAL_SEND, OUTPUT);
}

void loop()
{
        /* Start tracking motion */
        motion_sensor_tracker();
}
