#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../inc/lcd_wrapper.h"
#include "../inc/smart_bin.h"

/* Initialise LiquidCrystal_I2C object on address 0x27 */
static LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Used to track whether backlight is on or off */
static bool is_backlight_on = false;

/* Setting cursor on screen */
static void lcd_set_cursor(int y, int x)
{
        if (y>1 || x>15)
                return;

        lcd.setCursor(x,y);
}

/* prints text on screen */
static void lcd_print(const char* text)
{
        if (!text)
                return;

        lcd.print(text);
}

void lcd_init()
{
        /* initalise lcd */
        lcd.init();
        lcd_turn_backlight(true);

        /* Print intro sceen */
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("STARTING");
        lcd.setCursor(0,1);
        lcd.print("Smart bin v1.1");

        /* Wait for 2 seconds and turn off display */
        delay(2000);
        lcd_turn_backlight(false);
}

void lcd_clear()
{
        if (!is_backlight_on) {
                PRINT_DEBUG("trying to clear with backlight off");
                return;
        }

        lcd.clear();
}

void lcd_print_at(int y, int x, const char *text)
{
        /* Check for bad arguments */
        if (y>1 || x>15 || !text || strlen(text) > 16) {
                PRINT_DEBUG("Bad arguments.");
                lcd_print_at(0, 0, "PRINT ERROR");
                return;
        }

        /* Check whether backlight is on */
        if (!is_backlight_on) {
                PRINT_DEBUG("trying to write with backlight off");
                return;
        }

        /* Set cursor and print */
        lcd_set_cursor(y, x);
        lcd_print(text);
}

void lcd_turn_backlight(bool on)
{
        if (on) {
                /* Turn backlight on */
                lcd.backlight();
                is_backlight_on = true;
        } else {
                /* Clear text and turn backlight off */
                lcd.clear();
                lcd.noBacklight();
                is_backlight_on = false;
        }
}
