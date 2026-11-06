#ifndef INC_FSM_TRAFFIC_H_
#define INC_FSM_TRAFFIC_H_

#include "global.h"

// Các trạng thái của ngã tư
enum TrafficState {
    TRAFFIC_INIT,
    TRAFFIC_RED_GREEN,
    TRAFFIC_RED_YELLOW,
    TRAFFIC_GREEN_RED,
    TRAFFIC_YELLOW_RED
};

//EXTERNAL VARIABLES
// Biến lưu chế độ hoạt động của hệ thống (Normal, Config Đỏ, Vàng, Xanh, Manual)
extern int systemMode;
extern enum TrafficState traffic_state;

//FUNCTION PROTOTYPES

// Hàm máy trạng thái chính, gọi định kỳ qua Scheduler
void fsm_traffic_run(void);

#endif /* INC_FSM_TRAFFIC_H_ */
