#ifndef __I2C_LCD_H
#define __I2C_LCD_H
#include <main.h>
#include <stdbool.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

struct I2C_LCD_HandleTypeDef{
    I2C_HandleTypeDef *hi2c;
    uint8_t i2c_addr;
    uint8_t row_count;
    uint8_t col_count;
    bool backlight;
};

typedef struct I2C_LCD_HandleTypeDef I2C_LCD_HandleTypeDef;

void lcd_init(I2C_LCD_HandleTypeDef *hi2clcd);

void lcd_write_string(I2C_LCD_HandleTypeDef *hi2clcd, const char *str);

void lcd_clear(I2C_LCD_HandleTypeDef *hi2clcd);

void lcd_set_cursor(I2C_LCD_HandleTypeDef *hi2clcd, uint8_t row, uint8_t column);

#endif
