
#include "traffic_light.h"

void traffic_light_init(void)
{
    // Tắt đèn cho cả tuyến 1 và tuyến 2 lúc khởi động
    traffic_set(1, LIGHT_OFF);
    traffic_set(2, LIGHT_OFF);
}

void traffic_set(int line, int color)
{
    // Tách bit của biến 'color' (bit 1 cho tín hiệu A, bit 0 cho tín hiệu B)
    GPIO_PinState bit_A = ((color >> 1) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    GPIO_PinState bit_B = (color & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    if (line == 1)
    {
        HAL_GPIO_WritePin(TL1_A_GPIO_Port, TL1_A_Pin, bit_A);
        HAL_GPIO_WritePin(TL1_B_GPIO_Port, TL1_B_Pin, bit_B);
    }
    else if (line == 2)
    {
        HAL_GPIO_WritePin(TL2_A_GPIO_Port, TL2_A_Pin, bit_A);
        HAL_GPIO_WritePin(TL2_B_GPIO_Port, TL2_B_Pin, bit_B);
    }
}
