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

/* Servo object to which we call functions */
static Servo servo;

/* Variable keeps track of the bin that is currently opened */
static int opened_bin = 0;

int recieve_signal()
{
        /* Wait for signal transmition start, see development notes for further explanation */
        while (digitalRead(SIG_RECIEVE_PIN) == LOW)
                delay(10);

        volatile int bit;
        int signal_recv = 0;

        /* Checking for bad input */
        if (digitalRead(SIG_RECIEVE_PIN) != HIGH) {
                PRINT_DEBUG("Bad signal recieved");
                return -1;
        }

        /* Wait to be in the middle of bit transmition */
        delay(140);
        /* Scan 4 bits and bitwise or them together */
        for (size_t i = 0; i < 4; i++) {
                bit = digitalRead(SIG_RECIEVE_PIN);
                signal_recv |= bit << i;
                /* Wait for the middle of transmision of next bit*/
                delay(SIGNAL_BIT_RECV_PERIOD);
        }

        PRINT_DEBUG("Recieved signal:");
        PRINT_DEBUG(signal_recv);

        /* Check whether signal is valid, return error if not */
        if (signal_recv < 0 || signal_recv > 15)
                return -1;
        else
                return signal_recv;
}

void handle_signal(int signal)
{
        if (signal < 0)
                return;

        /* Call appropriate function based on signal */
        switch (signal)
        {
        case SIGNAL_BIN_1:      /* fall-through */
        case SIGNAL_BIN_2:      /* fall-through */
        case SIGNAL_BIN_3:      /* fall-through */
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
        /* Cannot open more than one bin at the same time */
        if (opened_bin != 0)
                return;

        /* get pin to be attacked and check it */
        int attached_pin = attach_pin(bin);
        if (attached_pin < 0)
                return;

        /* Detach in case of already attached pin and attach the new one */
        servo.detach();
        servo.attach(attached_pin);

        PRINT_DEBUG("Opening bin");
        PRINT_DEBUG(attached_pin);

        /* Turn servo motor 90 degrees */
        for (int i = 0; i < 1024; i+=8) {
                servo.write(map(i, 0, 1023, 0, 90));
                delay(10);
        }

        /* Set last opened bin variable to the currently opened bin */
        opened_bin = bin;
}

static void close_bin()
{
        /* Cannot close bin if no bin is opened */
        if (opened_bin == 0)
                return;

        /* get pin to be attacked and check it */
        int attached_pin = attach_pin(opened_bin);
        if (attached_pin < 0)
                return;

        /* Detach in case of already attached pin and attach the new one */
        servo.detach();
        servo.attach(attached_pin);

        PRINT_DEBUG("Closing bin");
        /* Turn the servo to it's normal position */
        servo.write(map(0, 0, 1023, 0, 180));

        /* Wait for servo to return and set the opened bin to closed bin */
        delay(100);
        opened_bin = BIN_CLOSE;
}

static int attach_pin(int bin)
{
        /* Check for invalid bin number. MUST BE BETWEEN 0 AND 4 !!! */
        if (bin < 0 || bin > 4)
                return -1;

        /* Pair list for every bin/pin combination */
        /* Note that bins are numbered 1-4, therefore the first row is unused */
        static int pairs [5][2] = {
                {0           , 0        },
                {SIGNAL_BIN_1, PIN_BIN_1},
                {SIGNAL_BIN_2, PIN_BIN_2},
                {SIGNAL_BIN_3, PIN_BIN_3},
                {SIGNAL_BIN_4, PIN_BIN_4}
        };

        /* Return appropriate pin from the list based on bin */
        return pairs[bin][1];
}
