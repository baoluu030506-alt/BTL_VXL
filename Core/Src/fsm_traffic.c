#include "fsm_traffic.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "button.h"
#include "i2c_lcd.h"

/* --- GLOBAL VARIABLES --- */
int systemMode = 1; // 1: NORMAL, 2: CFG_RED, 3: CFG_YELLOW, 4: CFG_GREEN, 5: MANUAL
enum TrafficState traffic_state = TRAFFIC_INIT;

/* --- FUNCTION IMPLEMENTATIONS --- */

void fsm_traffic_run(void) {

    // TODO: Đọc các nút nhấn (isButtonPressed) để chuyển đổi qua lại giữa các systemMode (Normal -> Config -> Manual) trước khi vào switch

    switch (systemMode) {
        // Chế độ hoạt động bình thường (Tự động)
        case 1: // MODE_1_NORMAL
            switch (traffic_state) {
                case TRAFFIC_INIT:

                    break;

                case TRAFFIC_RED_GREEN:

                    break;

                case TRAFFIC_RED_YELLOW:

                    break;

                case TRAFFIC_GREEN_RED:

                    break;

                case TRAFFIC_YELLOW_RED:

                    break;
            }
            break;

        // Chế độ điều chỉnh thời gian cho RED
        case 2: // MODE_2_RED

            break;

        // Chế độ điều chỉnh thời gian cho YELLOW
        case 3: // MODE_3_YELLOW

            break;

        // Chế độ điều chỉnh thời gian cho GREEN
        case 4: // MODE_4_GREEN

            break;

        // Chế độ điều khiển bằng tay (Manual)
        case 5: // MODE_5_MANUAL
            // TODO: Ép traffic_state = TRAFFIC_INIT
            // TODO: Đọc nút nhấn để ép đổi tín hiệu các đèn theo ý người dùng
            // TODO: Hiển thị trạng thái Manual lên LCD
            break;
    }
}
