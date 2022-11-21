# Development notes

## Master - slave communication
Since both I2C pins are already occupied by LC display, a different way of sending signal to the slave
board is used. Using one cable, a signal with value between 0 and 15 (inclusive) can be sent.
The way this is done is shown eigher here or in the master-slave-communication diagram located withing this fodler.

master board.
1. 0ms - Sends 1 to the slave board to annouce transmition 1
2. 100ms - Sends LSB (least significant bit) first, waits 100ms 000<u>0</u>
3. 200ms - Sends second LSB, waits 100ms 00<u>0</u>0
4. 300ms - Sends second MSB, waits 100ms 0<u>0</u>00
5. 400ms - Sends MSB, waits 100ms <u>0</u>000
6. 500ms - "Sends" 0, announcing end of transmition.

slave board.
1. 0ms - Recieves 1, preparing for transmition, waits for 140ms to be in middle of bit transmition period
2. ~150ms - Reciev LSB, waits 100 seconds
3. ~250ms - Reciev second LSB, waits 100 seconds
4. ~350ms - Reciev second MSB, waits 100 seconds
5. ~450ms - Reciev MSB, ends recieving
6. Checks signal value and if valid, handles it

Currently implemented signals:
* 1 - Open bin 1
* 2 - Open bin 2
* 3 - Open bin 3
* 4 - Open bin 4
* 15 - Close currently opened bin
