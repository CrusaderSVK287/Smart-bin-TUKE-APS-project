#include <Arduino.h>
#include "inc/motors.h"

void setup()
{
        /* Initialise serial port communication */
        Serial.begin(SERIAL_PORT);
        Serial.println("SLAVE BOARD STARTING SERIAL COMMUNICATION ON 9600");

        /* Set pin modes */
        pinMode(SIG_RECIEVE_PIN, INPUT);

        pinMode(PIN_BIN_1, OUTPUT);
        pinMode(PIN_BIN_2, OUTPUT);
        pinMode(PIN_BIN_3, OUTPUT);
        pinMode(PIN_BIN_4, OUTPUT);
}

void loop()
{
        /* Recieve signal */
        int sig = recieve_signal();
        /* If signal valid (>0) then handle it */
        if (sig >= 0) {
                handle_signal(sig);
        }
}
