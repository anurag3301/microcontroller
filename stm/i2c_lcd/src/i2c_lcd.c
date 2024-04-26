#include <i2c_lcd.h>
#include <main.h>

#define RS_BIT 0 // Register select bit
#define EN_BIT 2 // Enable bit
#define BL_BIT 3 // Backlight bit
#define D4_BIT 4 // Data 4 bit

void lcd_write_nibble(I2C_LCD_HandleTypeDef *hi2clcd, uint8_t nibble, uint8_t rs){
    uint8_t data = nibble << D4_BIT;
    data |= rs << RS_BIT;
    data |= hi2clcd->backlight << BL_BIT;
    data |= 1 << EN_BIT;
    HAL_I2C_Master_Transmit(hi2clcd->hi2c, hi2clcd->i2c_addr << 1, &data, 1, 100);
    HAL_Delay(1);
    data &= ~(1 << EN_BIT);
    HAL_I2C_Master_Transmit(hi2clcd->hi2c, hi2clcd->i2c_addr << 1, &data, 1, 100);
}

void lcd_send_cmd(I2C_LCD_HandleTypeDef *hi2clcd, uint8_t cmd){
    uint8_t upper_nibble = cmd >> 4;
    uint8_t lower_nibble = cmd & 0x0F;
    lcd_write_nibble(hi2clcd, upper_nibble, 0);
    lcd_write_nibble(hi2clcd, lower_nibble, 0);
    if(cmd == LCD_CLEARDISPLAY || cmd == LCD_RETURNHOME){
        HAL_Delay(2);
    }
}

void lcd_send_data(I2C_LCD_HandleTypeDef *hi2clcd, uint8_t data){
    uint8_t upper_nibble = data >> 4;
    uint8_t lower_nibble = data & 0x0F;
    lcd_write_nibble(hi2clcd, upper_nibble, 1);
    lcd_write_nibble(hi2clcd, lower_nibble, 1);
}


void lcd_init(I2C_LCD_HandleTypeDef *hi2clcd){
    HAL_Delay(50);

  	//put the LCD into 4 bit mode
    lcd_write_nibble(hi2clcd, 0x03, 0);
    HAL_Delay(5);
    lcd_write_nibble(hi2clcd, 0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(hi2clcd, 0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(hi2clcd, 0x02, 0);
    
    uint8_t displayfunction = LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
    lcd_send_cmd(hi2clcd, displayfunction); // 0x28

	uint8_t displaycontrol = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_send_cmd(hi2clcd, displaycontrol); // 0x0C

    lcd_clear(hi2clcd);

	uint8_t displaymode = LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	lcd_send_cmd(hi2clcd, displaymode); // 0x06
}

void lcd_write_string(I2C_LCD_HandleTypeDef *hi2clcd, const char *str){
    for(size_t i=0; str[i]!='\0'; i++){
        lcd_send_data(hi2clcd, str[i]);
    }
}


void lcd_clear(I2C_LCD_HandleTypeDef *hi2clcd){
    lcd_send_cmd(hi2clcd, 0x01);
    HAL_Delay(2);
}


void lcd_set_cursor(I2C_LCD_HandleTypeDef *hi2clcd, uint8_t row, uint8_t column) {
    uint8_t address;
    switch (row) {
        case 0:
            address = 0x00;
            break;
        case 1:
            address = 0x40;
            break;
        default:
            address = 0x00;
    }
    address += column;
    lcd_send_cmd(hi2clcd, LCD_SETDDRAMADDR | address);
}


