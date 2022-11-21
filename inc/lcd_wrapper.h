#ifndef LCD_H
#define LCD_H

/**
 * @brief Initialises LCD display, must be called in the setup function
 */
void lcd_init();

/**
 * @brief Clears the LCD display, Backlight must be on
 */
void lcd_clear();

/**
 * @brief Sets the cursor to given position based on y and x coorindates
 * and then prints the given text. Backlight must be on
 * @param y the row
 * @param x the column
 * @param text the text to print
 */
void lcd_print_at(int y, int x, const char* text);

/**
 * @brief Function turns backlight on or off, depending on
 *        given parameter
 *
 * @param on specifies whether backlight should be turned on or off
 */
void lcd_turn_backlight(bool on);

#endif /* LCD_H */
