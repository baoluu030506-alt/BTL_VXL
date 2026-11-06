#include "traffic_light.h"

//FUNCTION IMPLEMENTATIONS

void traffic_light_init(void) {
    // TODO: Gọi hàm traffic_set để tắt đèn (LIGHT_OFF) cho cả tuyến 1 và tuyến 2 lúc khởi động
}

void traffic_set(int line, int color) {
    // TODO: Tách bit của biến 'color' (bit 1 cho tín hiệu A, bit 0 cho tín hiệu B)

    if (line == 1) {
        // TODO: Dùng HAL_GPIO_WritePin xuất tín hiệu ra chân TL1_A_Pin và TL1_B_Pin
    }
    else if (line == 2) {
        // TODO: Dùng HAL_GPIO_WritePin xuất tín hiệu ra chân TL2_A_Pin và TL2_B_Pin
    }
}
