#include "i2c_lcd.h"

// EXTERNAL VARIABLES
// Khai báo extern biến hi2c1 (đã được CubeMX tạo trong main.c)
// để có thể dùng các hàm HAL_I2C_Master_Transmit truyền dữ liệu
extern I2C_HandleTypeDef hi2c1;

//FUNCTION IMPLEMENTATIONS

void lcd_send_cmd(char cmd) {
    // TODO: Viết logic tách byte và gửi lệnh command qua I2C đến địa chỉ LCD_I2C_ADDR
}

void lcd_send_data(char data) {
    // TODO: Viết logic tách byte và gửi dữ liệu ký tự qua I2C đến địa chỉ LCD_I2C_ADDR
}

void lcd_init(void) {
    // TODO: Gửi lần lượt các lệnh khởi tạo LCD (0x33, 0x32, 0x28, 0x0C, 0x01,...)
}

void lcd_goto_xy(int row, int col) {
    // TODO: Tính toán địa chỉ DDRAM dựa vào row và col, sau đó gọi lcd_send_cmd()
}

void lcd_send_string(char *str) {
    // TODO: Dùng vòng lặp duyệt qua chuỗi str và gọi lcd_send_data() cho từng ký tự
}

void lcd_clear(void) {
    // TODO: Gửi lệnh xóa màn hình (0x01) và delay ngắn để LCD kịp xử lý
}
