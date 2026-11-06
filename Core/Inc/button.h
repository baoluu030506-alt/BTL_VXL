#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NO_OF_BUTTONS 4 //4 nút nhấn

//FUNCTION PROTOTYPES

// Hàm đọc trạng thái và chống dội (sẽ được Scheduler gọi định kỳ)
void button_reading(void);

// Hàm kiểm tra trạng thái vật lý của nút nhấn (đã qua chống rung)
unsigned char is_button_pressed(uint8_t index);

// Hàm kiểm tra xem 1 nút cụ thể đã được nhấn giữ >= 1s hay chưa
unsigned char is_button_pressed_1s(uint8_t index);

#endif /* INC_BUTTON_H_ */
