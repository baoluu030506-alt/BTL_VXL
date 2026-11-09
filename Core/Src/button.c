#include "button.h"

// Tính số chu kỳ tự động dựa theo TICK_MS (được định nghĩa trong global.h)
#define DURATION_FOR_AUTO_INCREASING (1000 / TICK_MS)

#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

// Mảng ánh xạ các chân GPIO tương ứng với 4 button (sử dụng User Label từ file .ioc)
static uint16_t button_pins[NO_OF_BUTTONS] = {BTN_1_Pin, BTN_2_Pin, BTN_3_Pin, BTN_4_Pin};
static GPIO_TypeDef* button_ports[NO_OF_BUTTONS] = {BTN_1_GPIO_Port, BTN_2_GPIO_Port, BTN_3_GPIO_Port, BTN_4_GPIO_Port};

// Bộ đệm lưu trạng thái cuối cùng sau khi debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

// Định nghĩa 2 bộ đệm để debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

// Cờ ghi nhận sự kiện nhấn nút > 1s
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0, 0};

// Bộ đếm cho sự kiện nhấn giữ > 1s
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0, 0};

//FUNCTION IMPLEMENTATIONS

void button_reading(void) {
    for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i];

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                }
            } else {
                counterForButtonPress1s[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

unsigned char is_button_pressed(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED) ? 1 : 0;
}

unsigned char is_button_pressed_1s(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;

    if (flagForButtonPress1s[index] == 1) {
        flagForButtonPress1s[index] = 0;   
        return 1;
    }
    return 0;
}
