#include "dht20.h"

//EXTERNAL VARIABLES
// Khai báo extern hi2c1 để dùng chung bộ I2C1 với LCD
extern I2C_HandleTypeDef hi2c1;

//LOCAL VARIABLES
static float temperature = 0.0f;
static float humidity = 0.0f;

//FUNCTION IMPLEMENTATIONS

void dht20_init(void) {
    // TODO: Gửi lệnh kiểm tra trạng thái (0x71) qua I2C đến DHT20_I2C_ADDR
    // TODO: Nếu cảm biến chưa sẵn sàng, gửi chuỗi lệnh khởi tạo theo datasheet
}

void dht20_read(void) {
    // TODO: Gửi lệnh kích hoạt đo đạc (thường là 0xAC, 0x33, 0x00)
    // TODO: Đọc 7 byte dữ liệu trả về từ cảm biến
    // TODO: Tách bit và áp dụng công thức trong datasheet để cập nhật biến temperature và humidity
}

float dht20_get_temperature(void) {
    return temperature;
}

float dht20_get_humidity(void) {
    return humidity;
}
