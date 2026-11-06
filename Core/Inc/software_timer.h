#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_

#include "global.h"

#define MAX_TIMERS    5

// Mảng cờ báo hiệu timeout cho các module khác sử dụng (như fsm_traffic)
extern int timer_flag[MAX_TIMERS];

//FUNCTION PROTOTYPES

// Cài đặt timer
void setTimer(int index, int duration_ms);

// Xóa/dừng timer
void clearTimer(int index);

// Hàm cập nhật các biến đếm (sẽ được Scheduler gọi định kỳ như một Task)
void timerRun(void);

#endif /* INC_SOFTWARETIMER_H_ */
