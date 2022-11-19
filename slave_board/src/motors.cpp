#include <Arduino.h>
#include "../inc/motors.h"

#define BIN_OPEN 1
#define BIN_CLOSE 0

#define SIGNAL_OPEN_BIN_1 1
#define SIGNAL_OPEN_BIN_2 2
#define SIGNAL_OPEN_BIN_3 3
#define SIGNAL_OPEN_BIN_4 4
#define SIGNAL_CLOSE_OPENED_BIN 15

/*
 * Function open of close bins, each for one due to different motors.
 * Parameter open indicates whether bin should be opened ( value > 0),
 * or close ( value <= 0 ).
 */
static void handle_bin_1(int open);
static void handle_bin_2(int open);
static void handle_bin_3(int open);
static void handle_bin_4(int open);
/* Calls handle bin function to close the bin */
static void close_bin();

static int opened_bin;

int recieve_signal()
{
        while (digitalRead(SIG_RECIEVE_PIN) == LOW)
                delay(10);

        volatile int bit;
        int recieved_signal = 0;

        /* Checking for bad input */
        if (digitalRead(SIG_RECIEVE_PIN) != HIGH) {
                PRINT_DEBUG("Bad signal recieved");
                return -1;
        }

        delay(140);
        for (size_t i = 0; i < 4; i++) {
                bit = digitalRead(SIG_RECIEVE_PIN);
                recieved_signal |= bit << i;
                delay(100);
        }

        PRINT_DEBUG("Recieved signal:");
        PRINT_DEBUG(recieved_signal);

        if (recieved_signal < 0 || recieved_signal > 15)
                return -1;
        else
                return recieved_signal;
}

void handle_signal(int signal)
{
        if (signal < 0)
                return;

        switch (signal)
        {
        case SIGNAL_OPEN_BIN_1: handle_bin_1(BIN_OPEN);
                break;
        case SIGNAL_OPEN_BIN_2: handle_bin_2(BIN_OPEN);
                break;
        case SIGNAL_OPEN_BIN_3: handle_bin_3(BIN_OPEN);
                break;
        case SIGNAL_OPEN_BIN_4: handle_bin_4(BIN_OPEN);
                break;
        case SIGNAL_CLOSE_OPENED_BIN: close_bin();
                break;
        default:
                break;
        }
}

static void handle_bin_1(int open)
{
        if ((open == BIN_OPEN && opened_bin != 0) ||
                (open == BIN_CLOSE && opened_bin == 0))
                return;
}

static void handle_bin_2(int open)
{
        if ((open == BIN_OPEN && opened_bin != 0) ||
                (open == BIN_CLOSE && opened_bin == 0))
                return;
}

static void handle_bin_3(int open)
{
        if ((open == BIN_OPEN && opened_bin != 0) ||
                (open == BIN_CLOSE && opened_bin == 0))
                return;
}

static void handle_bin_4(int open)
{
        if ((open == BIN_OPEN && opened_bin != 0) ||
                (open == BIN_CLOSE && opened_bin == 0))
                return;
}

static void close_bin()
{
        switch (opened_bin)
        {
        case SIGNAL_OPEN_BIN_1: handle_bin_1(BIN_CLOSE);
                break;
        case SIGNAL_OPEN_BIN_2: handle_bin_2(BIN_CLOSE);
                break;
        case SIGNAL_OPEN_BIN_3: handle_bin_3(BIN_CLOSE);
                break;
        case SIGNAL_OPEN_BIN_4: handle_bin_4(BIN_CLOSE);
                break;
        default:
                break;
        }
}