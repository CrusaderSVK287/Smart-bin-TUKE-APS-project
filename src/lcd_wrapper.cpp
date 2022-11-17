#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../inc/lcd_wrapper.h"
#include "../inc/smart_bin.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static bool is_backlight_on = false;

static void lcd_set_cursor(int y, int x)
{
        if (y>1 || x>15)
                return;

        lcd.setCursor(x,y);
}


static void lcd_print(const char* text)
{
        if (!text)
                return;

        lcd.print(text);
}

void lcd_init()
{
        lcd.init();
        lcd_turn_backlight(true);
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("STARTING");
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
        if (y>1 || x>15 || !text) {
                PRINT_DEBUG("Bad arguments.");
                lcd_print_at(0, 0, "PRINT ERROR");
                return;
        }

        if (!is_backlight_on) {
                PRINT_DEBUG("trying to write with backlight off");
                return;
        }

        lcd_set_cursor(y, x);
        lcd_print(text);
}

void lcd_turn_backlight(bool on)
{
        if (on) {
                lcd.backlight();
                is_backlight_on = true;
        } else {
                lcd.clear();
                lcd.noBacklight();
                is_backlight_on = false;
        }
}
