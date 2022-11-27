#ifndef SMART_BIN_H
#define SMART_BIN_H

#include <Arduino.h>

/* Serial port for communication */
#define SERIAL_PORT 9600

/* Timeouts for choosing bin and closing bin */
#define TIMEOUT 20000
#define BIN_CLOSE_TIMEOUT 10000

/* defined pins */
#define MOTION_SENSOR_PIN PIN7
#define PIN_BTN_1 PIN_A3
#define PIN_BTN_2 PIN_A2
#define PIN_BTN_3 PIN_A1
#define PIN_BTN_4 PIN_A0
#define PIN_SIGNAL_SEND PIN2


/*
 * If you wish to get debug information, define DEBUG before this ifdef.
 * Please refrain from keeping DEBUG defined when pushing to SC.
 * Check before submiting for a pull request
 */
#define DEBUG
#ifdef DEBUG
#define PRINT_DEBUG(MSG) Serial.print(MSG);             \
                         Serial.print(" ");             \
                         Serial.print(__FILE__);        \
                         Serial.print(":");             \
                         Serial.println(String(__LINE__))
#else
#define PRINT_DEBUG(MSG)
#endif /* DEBUG */

/**
 * @brief Function tracks input from the motion sensor.
 *        Once sensor is activated, calls another function
 *        to handle the button input
 */
void motion_sensor_tracker();

/**
 * @brief Function prints information on display and
 * 	  waits for user to press one of the buttons
 * 	  that will open a container
 */
void wait_and_handle_selection();

/**
 * @brief Function sends 4 bit signal from signal pin
 * @param sig signal number to be sent (between 1 and 15 inclusive)
 */
void send_signal(int sig);

#endif /* SMART_BIN_H */
