#include "software_timer.h"

//LOCAL/GLOBAL VARIABLES
int timer_counter[MAX_TIMERS] = {0};
int timer_flag[MAX_TIMERS] = {0};

//FUNCTION IMPLEMENTATIONS

void setTimer(int index, int duration) {
    // TODO: Viết logic quy đổi duration_ms sang số tick (chia cho TICK_MS) và gán cho timer_counter
	if(index < 0 || index >= MAX_TIMERS) return;

	timer_counter[index] = duration / TICK_MS;

	timer_flag[index] = 0;
}

void clearTimer(int index) {
    // TODO: Xóa timer_counter và timer_flag của index tương ứng về 0
	if(index < 0 || index >= MAX_TIMERS) return;

	timer_counter[index] = 0;
	timer_flag[index] = 0;
}

void timerRun(void) {
    // TODO: Viết vòng lặp duyệt qua các timer, nếu counter > 0 thì trừ đi 1, khi về 0 thì bật flag = 1
	for(int i = 0; i < MAX_TIMERS; i++){
		if(timer_counter[i] > 0 ){
			timer_counter[i]--;
			if(timer_counter[i] <= 0) timer_flag[i] = 1;
		}
	}
}
