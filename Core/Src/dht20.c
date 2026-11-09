#include "dht20.h"

// EXTERNAL VARIABLES
extern I2C_HandleTypeDef hi2c1;

// LOCAL VARIABLES
static float temperature = 0.0f;
static float humidity = 0.0f;
static uint8_t is_triggered = 0;

// FUNCTION IMPLEMENTATIONS

void dht20_init(void)
{
    // Theo Datasheet DHT20: Cần chờ ít nhất 100ms sau khi cấp điện để cảm biến ổn định
    HAL_Delay(100);

    uint8_t status_cmd = 0x71;
    uint8_t status_val = 0;

    // Kiểm tra trạng thái cảm biến
    if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, &status_cmd, 1, 100) == HAL_OK)
    {
        HAL_I2C_Master_Receive(&hi2c1, DHT20_I2C_ADDR, &status_val, 1, 100);

        // Nếu bit校准 (bit 3) chưa bằng 1, gửi lệnh reset thanh ghi theo datasheet DHT20
        if ((status_val & 0x18) != 0x18)
        {
            uint8_t init_cmd1[3] = {0x1B, 0x00, 0x00};
            uint8_t init_cmd2[3] = {0x1C, 0x00, 0x00};
            uint8_t init_cmd3[3] = {0x1E, 0x00, 0x00};
            HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, init_cmd1, 3, 100);
            HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, init_cmd2, 3, 100);
            HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, init_cmd3, 3, 100);
            HAL_Delay(10);
        }
    }

    // Gửi lệnh kích hoạt đo lần đầu tiên (0xAC, 0x33, 0x00)
    uint8_t trig_cmd[3] = {0xAC, 0x33, 0x00};
    if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, trig_cmd, 3, 100) == HAL_OK)
    {
        is_triggered = 1;
    }
}

void dht20_read(void)
{
    uint8_t rx_data[7] = {0};
    uint8_t trig_cmd[3] = {0xAC, 0x33, 0x00};

    // 1. Đọc 7 byte dữ liệu từ lần kích hoạt trước
    if (is_triggered)
    {
        if (HAL_I2C_Master_Receive(&hi2c1, DHT20_I2C_ADDR, rx_data, 7, 100) == HAL_OK)
        {
            // Kiểm tra Bit 7 (Busy == 0) và dữ liệu nhận về khác 0
            if ((rx_data[0] & 0x80) == 0x00 && (rx_data[1] != 0 || rx_data[2] != 0 || rx_data[4] != 0))
            {
                uint32_t raw_hum = ((uint32_t)rx_data[1] << 12)
                                 | ((uint32_t)rx_data[2] << 4)
                                 | ((uint32_t)(rx_data[3] >> 4));

                uint32_t raw_temp = (((uint32_t)(rx_data[3] & 0x0F)) << 16)
                                  | ((uint32_t)rx_data[4] << 8)
                                  | ((uint32_t)rx_data[5]);

                humidity    = ((float)raw_hum * 100.0f) / 1048576.0f;
                temperature = (((float)raw_temp * 200.0f) / 1048576.0f) - 50.0f;
            }
        }
    }

    // 2. Luôn gửi lại lệnh Trigger (0xAC, 0x33, 0x00) cho chu kỳ đọc sau (2 giây sau)
    if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, trig_cmd, 3, 100) == HAL_OK)
    {
        is_triggered = 1;
    }
}

float dht20_get_temperature(void)
{
    return temperature;
}

float dht20_get_humidity(void)
{
    return humidity;
}
