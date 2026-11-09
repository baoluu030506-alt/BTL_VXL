#define LCD_BACKLIGHT 0x08
#define LCD_EN        0x04
#define LCD_RS        0x01

#include "i2c_lcd.h"

// EXTERNAL VARIABLES
// Khai báo extern biến hi2c1 (đã được CubeMX tạo trong main.c)
// để có thể dùng các hàm HAL_I2C_Master_Transmit truyền dữ liệu
extern I2C_HandleTypeDef hi2c1;

//FUNCTION IMPLEMENTATIONS

void lcd_send_cmd(char cmd) {
    uint8_t data_u = (cmd & 0xF0);          
    uint8_t data_l = ((cmd << 4) & 0xF0);   
    uint8_t data_t[4];

    data_t[0] = data_u | LCD_BACKLIGHT | LCD_EN;
    data_t[1] = data_u | LCD_BACKLIGHT;
    data_t[2] = data_l | LCD_BACKLIGHT | LCD_EN;
    data_t[3] = data_l | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data_t, 4, 100);
}

void lcd_send_data(char data) {
    uint8_t data_u = (data & 0xF0);
    uint8_t data_l = ((data << 4) & 0xF0);
    uint8_t data_t[4];

    data_t[0] = data_u | LCD_BACKLIGHT | LCD_EN | LCD_RS;
    data_t[1] = data_u | LCD_BACKLIGHT | LCD_RS;
    data_t[2] = data_l | LCD_BACKLIGHT | LCD_EN | LCD_RS;
    data_t[3] = data_l | LCD_BACKLIGHT | LCD_RS;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data_t, 4, 100);
}

void lcd_init(void) {
    HAL_Delay(50);         

    lcd_send_cmd(0x33);     
    lcd_send_cmd(0x32);    
    lcd_send_cmd(0x28);    
    lcd_send_cmd(0x0C);    
    lcd_send_cmd(0x06);     
    lcd_send_cmd(0x01);     
    HAL_Delay(2);          
}

void lcd_goto_xy(int row, int col) {
    uint8_t addr;

    switch (row) {
        case 0:  addr = 0x00 + col; break;
        case 1:  addr = 0x40 + col; break;
        case 2:  addr = 0x14 + col; break;   
        case 3:  addr = 0x54 + col; break;   
        default: addr = 0x00 + col; break;
    }

    lcd_send_cmd(0x80 | addr);   
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    HAL_Delay(2);   
}