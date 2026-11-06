#include "softwaretimer.h"

//LOCAL/GLOBAL VARIABLES
int timer_counter[MAX_TIMERS] = {0};
int timer_flag[MAX_TIMERS] = {0};

//FUNCTION IMPLEMENTATIONS

void setTimer(int index, int duration_ms) {
    // TODO: Viết logic quy đổi duration_ms sang số tick (chia cho TICK_MS) và gán cho timer_counter
}

void clearTimer(int index) {
    // TODO: Xóa timer_counter và timer_flag của index tương ứng về 0
}

void timerRun(void) {
    // TODO: Viết vòng lặp duyệt qua các timer, nếu counter > 0 thì trừ đi 1, khi về 0 thì bật flag = 1
}
