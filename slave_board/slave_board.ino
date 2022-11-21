#include <Arduino.h>
#include "inc/motors.h"

void setup()
{
        Serial.begin(SERIAL_PORT);
        Serial.println("SLAVE BOARD STARTING SERIAL COMMUNICATION ON 9600");

        pinMode(SIG_RECIEVE_PIN, INPUT);

        pinMode(PIN_BIN_1, OUTPUT);
        pinMode(PIN_BIN_2, OUTPUT);
        pinMode(PIN_BIN_3, OUTPUT);
        pinMode(PIN_BIN_4, OUTPUT);
}

void loop()
{
        int sig = recieve_signal();
        if (sig >= 0) {
                handle_signal(sig);
        }
}
