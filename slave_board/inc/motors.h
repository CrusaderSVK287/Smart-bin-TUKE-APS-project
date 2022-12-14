#ifndef MOTORS_H
#define MOTORS_H

/* Serial port for communication */
#define SERIAL_PORT 9600

/* defined pins */
#define SIG_RECIEVE_PIN PIN_A0
#define PIN_BIN_1 PIN4
#define PIN_BIN_2 PIN5
#define PIN_BIN_3 PIN6
#define PIN_BIN_4 PIN7

/*
 * If you wish to get debug information, define DEBUG before this ifdef.
 * Please refrain from keeping DEBUG defined when pushing to SC.
 * Check before submiting for a pull request
 */
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
 * @brief Function waits for signal from master board.
 * @return signal number or -1 on errors
 */
int recieve_signal();

/**
 * @brief Function handles signal based on its number
 * @param signal signal number
 */
void handle_signal(int signal);

#endif /* MOTORS_H */
