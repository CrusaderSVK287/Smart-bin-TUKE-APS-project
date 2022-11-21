#include <Arduino.h>
#include <Servo.h>
#include "../inc/motors.h"

#define SIGNAL_BIT_RECV_PERIOD 100

#define BIN_OPEN 1
#define BIN_CLOSE 0

#define SIGNAL_BIN_1 1
#define SIGNAL_BIN_2 2
#define SIGNAL_BIN_3 3
#define SIGNAL_BIN_4 4
#define SIGNAL_CLOSE_OPENED_BIN 15

/*
 * Function open of close bins, each for one due to different motors.
 * Parameter open indicates whether bin should be opened ( value > 0),
 * or close ( value <= 0 ).
 */
static void open_bin(int bin);

/*
 * Function returns pin corresponsing with the appropriate bin
 */
static int attach_pin(int bin);

/* Calls handle bin function to close the bin */
static void close_bin();

static Servo servo;

static int opened_bin = 0;

int recieve_signal()
{
        while (digitalRead(SIG_RECIEVE_PIN) == LOW)
                delay(10);

        volatile int bit;
        int signal_recv = 0;

        /* Checking for bad input */
        if (digitalRead(SIG_RECIEVE_PIN) != HIGH) {
                PRINT_DEBUG("Bad signal recieved");
                return -1;
        }

        delay(140);
        for (size_t i = 0; i < 4; i++) {
                bit = digitalRead(SIG_RECIEVE_PIN);
                signal_recv |= bit << i;
                delay(SIGNAL_BIT_RECV_PERIOD);
        }

        PRINT_DEBUG("Recieved signal:");
        PRINT_DEBUG(signal_recv);

        if (signal_recv < 0 || signal_recv > 15)
                return -1;
        else
                return signal_recv;
}

void handle_signal(int signal)
{
        if (signal < 0)
                return;

        switch (signal)
        {
        case SIGNAL_BIN_1:
        case SIGNAL_BIN_2:
        case SIGNAL_BIN_3:
        case SIGNAL_BIN_4: open_bin(signal);
                break;
        case SIGNAL_CLOSE_OPENED_BIN: close_bin();
                break;
        default:
                break;
        }
}

static void open_bin(int bin)
{
        if (opened_bin != 0)
                return;

        int attached_pin = attach_pin(bin);
        if (attached_pin < 0)
                return;

        servo.detach();
        servo.attach(attached_pin);

        PRINT_DEBUG("Opening bin");
        PRINT_DEBUG(attached_pin);

        for (int i = 0; i < 1024; i+=8) {
                servo.write(map(i, 0, 1023, 0, 90));
                delay(10);
        }
        opened_bin = bin;
}

static void close_bin()
{
        if (opened_bin == 0)
                return;

        int attached_pin = attach_pin(opened_bin);
        if (attached_pin < 0)
                return;

        servo.detach();
        servo.attach(attached_pin);
        PRINT_DEBUG("Closing bin");
        servo.write(map(0, 0, 1023, 0, 180));

        opened_bin = BIN_CLOSE;
        delay(100);
}

static int attach_pin(int bin)
{
        if (bin < 0 || bin > 3)
                return -1;

        static int pairs [5][2] = {
                {0           , 0        },
                {SIGNAL_BIN_1, PIN_BIN_1},
                {SIGNAL_BIN_2, PIN_BIN_2},
                {SIGNAL_BIN_3, PIN_BIN_3},
                {SIGNAL_BIN_4, PIN_BIN_4}
        };

        return pairs[bin][1];
}
