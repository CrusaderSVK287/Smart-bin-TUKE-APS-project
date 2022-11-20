#include <Arduino.h>
#include "inc/motors.h"

void setup()
{
        Serial.begin(SERIAL_PORT);
        Serial.println("SLAVE BOARD STARTING SERIAL COMMUNICATION ON 9600");

        pinMode(SIG_RECIEVE_PIN, INPUT);
}

void loop()
{
        int sig = recieve_signal();
        if (sig >= 0) {
                handle_signal(sig);
        }
}
