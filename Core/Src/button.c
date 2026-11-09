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
    // TODO: Viết logic đọc nút nhấn, xử lý bộ đệm debounceButtonBuffer1 và debounceButtonBuffer2
    // TODO: Xử lý tăng counterForButtonPress1s và bật flagForButtonPress1s khi đủ thời gian
}

unsigned char is_button_pressed(uint8_t index) {
    // TODO: Kiểm tra buttonBuffer và trả về 1 nếu nút được nhấn
    return 0;
}

unsigned char is_button_pressed_1s(uint8_t index) {
    // TODO: Kiểm tra flagForButtonPress1s, xóa cờ và trả về kết quả
    return 0;
}
