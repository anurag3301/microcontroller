#ifndef __I2C_LCD_H
#define __I2C_LCD_H
#include <main.h>
#include <stdbool.h>

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
