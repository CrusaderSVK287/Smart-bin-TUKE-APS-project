#include "../inc/smart_bin.h"
#include "../inc/lcd_wrapper.h"
#include <Wire.h>

/* defining waiting periods */
#define SIG_CHECK_PERIOD 100
#define SIGNAL_SEND_PERIOD 100

/* Defining used pins */
#define SIG_CLOSE_BINS 15
#define SIG_OPEN_BIN1 1
#define SIG_OPEN_BIN2 2
#define SIG_OPEN_BIN3 3
#define SIG_OPEN_BIN4 4

/* Used to determine whether signal was send or not */
static bool signal_sent = false;

void motion_sensor_tracker()
{
        /* Waiting for motion to be detected */
        while(1) {
                if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
                        PRINT_DEBUG("Motion detected.");
                        wait_and_handle_selection();
                        break;
                }

                delay(1000);
        }
}

void wait_and_handle_selection()
{
        PRINT_DEBUG("Waiting for selection");
        int timeout = TIMEOUT;
        signal_sent = false;

        /* Turning on the display and displaying information */
        lcd_turn_backlight(true);

        lcd_print_at(0, 0, "1 Plast   3 Sklo");
        lcd_print_at(1, 0, "2 Papier  4 Kovy");

        /* Waiting for TIMEOUT seconds, eighter sending a signal or turning of display */
        for (timeout = TIMEOUT; timeout > 0; timeout -= SIG_CHECK_PERIOD) {
                /* Break out when signal is sent */
                if (signal_sent)
                        break;
                /* Sending signal if button pressed */
                else if (digitalRead(PIN_BTN_1) == HIGH)
                        send_signal(SIG_OPEN_BIN1);
                else if (digitalRead(PIN_BTN_2) == HIGH)
                        send_signal(SIG_OPEN_BIN2);
                else if (digitalRead(PIN_BTN_3) == HIGH)
                        send_signal(SIG_OPEN_BIN3);
                else if (digitalRead(PIN_BTN_4) == HIGH)
                        send_signal(SIG_OPEN_BIN4);

                delay(SIG_CHECK_PERIOD);
        }

        /* If signal sent, print info on display and set timeout */
        if (signal_sent) {
                lcd_clear();
                lcd_print_at(0, 0, "Kos sa otvara..");
                lcd_print_at(1, 0, "Prosim cakajte");
                timeout = BIN_CLOSE_TIMEOUT;
        }

        /* Wait for the remaining timeout (usually eighter BIN_CLOSE_TIMEOUT or 0 */
        delay(timeout);
        lcd_turn_backlight(false);

        /* If signal has been sent to open a bin, send a signal to close it */
        if (signal_sent)
                send_signal(SIG_CLOSE_BINS);
}

void send_signal(int sig)
{
        if (sig < 0 || sig > 0b1111) {
                PRINT_DEBUG("Bad signal number");
                return;
        }

        PRINT_DEBUG("Sending signal");
        PRINT_DEBUG(sig);

        signal_sent = true;

        /*
         * Since A4 and A5 I2C pins are already used by LCD display,
         * we will be using a different pin for communication to slave board.
         * See Development-notes.md "Master-slave-communication" section
         */
        digitalWrite(PIN_SIGNAL_SEND, HIGH);
        delay(100);

        for (size_t i = 0; i < 4; i++) {
                digitalWrite(PIN_SIGNAL_SEND, sig >> i & 1);
                delay(SIGNAL_SEND_PERIOD);
        }

        digitalWrite(PIN_SIGNAL_SEND, LOW);
}
