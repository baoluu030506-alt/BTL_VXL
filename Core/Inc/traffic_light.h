#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "global.h"

//COLOR DEFINITIONS
// Định nghĩa các hằng số màu sắc dựa trên bảng tổ hợp bit (Bước 3.2)
#define LIGHT_OFF       0   // Tổ hợp 00
#define LIGHT_AMBER     1   // Tổ hợp 01 (Vàng)
#define LIGHT_GREEN     2   // Tổ hợp 10 (Xanh)
#define LIGHT_RED       3   // Tổ hợp 11 (Đỏ)

//FUNCTION PROTOTYPES

// Hàm khởi tạo trạng thái ban đầu cho các đèn (thường là tắt hết)
void traffic_light_init(void);

// Hàm điều khiển đèn giao thông theo tuyến
// Tham số line: 1 (cho Trục 1) hoặc 2 (cho Trục 2)
// Tham số color: LIGHT_RED, LIGHT_GREEN, LIGHT_AMBER, hoặc LIGHT_OFF
void traffic_set(int line, int color);

#endif /* INC_TRAFFIC_LIGHT_H_ */
