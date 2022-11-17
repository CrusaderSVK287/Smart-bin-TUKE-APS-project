#ifndef SMART_BIN_H
#define SMART_BIN_H

#include <Arduino.h>

#define SERIAL_PORT 9600
#define MOTION_SENSOR_PIN PIN_A0

/*
 * If you wish to get debug information, define DEBUG before this ifdef.
 * Please refrain from keeping DEBUG defined when pushing to SC
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
void wait_for_selection();

#endif /* SMART_BIN_H */
