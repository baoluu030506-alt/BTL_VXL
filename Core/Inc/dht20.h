#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include "global.h"

//FUNCTION PROTOTYPES

// Hàm khởi tạo và cấu hình ban đầu cho cảm biến DHT20
void dht20_init(void);

// Hàm yêu cầu DHT20 đo đạc và đọc chuỗi byte dữ liệu về để tính toán
// Theo tài liệu (Bước 5), hàm này không nên gọi liên tục mà nên gọi theo chu kỳ (ví dụ 2 giây/lần)
void dht20_read(void);

// Hàm lấy giá trị nhiệt độ (đã qua tính toán) để hiển thị lên LCD
float dht20_get_temperature(void);

// Hàm lấy giá trị độ ẩm (đã qua tính toán) để hiển thị lên LCD
float dht20_get_humidity(void);

#endif /* INC_DHT20_H_ */
