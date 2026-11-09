#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_  

#include "global.h"

//FUNCTION PROTOTYPES

// Hàm khởi tạo màn hình LCD (chế độ 4-bit, bật hiển thị, xóa màn hình...)
void lcd_init(void);

// Hàm gửi 1 byte lệnh (command) xuống LCD
void lcd_send_cmd(char cmd);

// Hàm gửi 1 byte dữ liệu (ký tự hiển thị) xuống LCD
void lcd_send_data(char data);

// Hàm gửi một chuỗi ký tự xuống LCD
void lcd_send_string(char *str);

// Hàm di chuyển con trỏ chuột đến vị trí hàng (row) và cột (col)
// Hàng: thường là 0 hoặc 1. Cột: từ 0 đến 15 (với LCD 16x2)
void lcd_goto_xy(int row, int col);

// Hàm xóa toàn bộ nội dung trên màn hình LCD
void lcd_clear(void);

#endif /* INC_I2C_LCD_H_ */
