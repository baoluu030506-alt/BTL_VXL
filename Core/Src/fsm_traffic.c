#include "fsm_traffic.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "button.h"
#include "i2c_lcd.h"
#include "dht20.h"
#include <stdio.h>

/* --- GLOBAL VARIABLES --- */
int systemMode = 1; // 1: NORMAL, 2: CFG_RED, 3: CFG_YELLOW, 4: CFG_GREEN, 5: MANUAL
enum TrafficState traffic_state = TRAFFIC_INIT;

/* --- LOCAL VARIABLES --- */
static int temp_duration = 1; // Biến lưu thời gian tạm khi chỉnh ở Mode 2, 3, 4
static uint8_t blink_on = 0;  // Trạng thái bật/tắt (1/0) khi chớp đèn 2Hz

/* Hàm cập nhật hiển thị lên LCD 16x2 thông qua i2c_lcd.h */
static void update_lcd_display(void)
{
    char line0[17];
    char line1[17];

    switch (systemMode)
    {
    case 1: // Chế độ Tự động: Hàng 0 hiện đếm ngược 2 trục, Hàng 1 hiện Nhiệt độ & Độ ẩm
    {
        int temp_x10 = (int)(dht20_get_temperature() * 10.0f);
        int hum_x10  = (int)(dht20_get_humidity() * 10.0f);

        snprintf(line0, sizeof(line0), "AUTO 1:%02ds 2:%02ds", count_road1, count_road2);
        snprintf(line1, sizeof(line1), "T:%02d.%dC H:%02d.%d%%",
                 temp_x10 / 10, temp_x10 % 10,
                 hum_x10 / 10,  hum_x10 % 10);
        break;
    }

    case 2: // Chỉnh thời gian Đỏ
        snprintf(line0, sizeof(line0), "MODE 2: CFG RED ");
        snprintf(line1, sizeof(line1), "Set Time: %02ds   ", temp_duration);
        break;

    case 3: // Chỉnh thời gian Vàng
        snprintf(line0, sizeof(line0), "MODE 3: CFG YEL ");
        snprintf(line1, sizeof(line1), "Set Time: %02ds   ", temp_duration);
        break;

    case 4: // Chỉnh thời gian Xanh
        snprintf(line0, sizeof(line0), "MODE 4: CFG GRN ");
        snprintf(line1, sizeof(line1), "Set Time: %02ds   ", temp_duration);
        break;

    case 5: // Chế độ Bằng tay (Manual) - Có hiển thị đếm ngược khi đang chờ đèn Vàng
        snprintf(line0, sizeof(line0), "MODE 5: MANUAL  ");
        if (status == MAN_RED_GREEN)
        {
            snprintf(line1, sizeof(line1), "R1:RED   R2:GRN ");
        }
        else if (status == MAN_RED_YELLOW)
        {
            snprintf(line1, sizeof(line1), "R1:RED R2:Y(%02ds)", count_road2);
        }
        else if (status == MAN_GREEN_RED)
        {
            snprintf(line1, sizeof(line1), "R1:GRN   R2:RED ");
        }
        else if (status == MAN_YELLOW_RED)
        {
            snprintf(line1, sizeof(line1), "R1:Y(%02ds) R2:RED", count_road1);
        }
        break;
    }

    lcd_goto_xy(0, 0);
    lcd_send_string(line0);
    lcd_goto_xy(1, 0);
    lcd_send_string(line1);
}

/* --- FUNCTION IMPLEMENTATIONS --- */

void fsm_traffic_run(void)
{
    // 1. ĐỌC NÚT NHẤN 1 (index 0) ĐỂ CHUYỂN ĐỔI GIỮA CÁC CHẾ ĐỘ (Normal -> Config -> Manual)
    if (is_button_pressed(0))
    {
        systemMode++;
        if (systemMode > 5)
        {
            systemMode = 1;
        }

        // Thiết lập trạng thái an toàn ngay khi chuyển Mode
        if (systemMode == 1)
        {
            traffic_state = TRAFFIC_INIT;
            status = INIT;
        }
        else if (systemMode == 2)
        {
            status = CFG_RED;
            temp_duration = time_red;
            blink_on = 0;
            traffic_light_init();
            setTimer(1, 250);
            update_lcd_display();
        }
        else if (systemMode == 3)
        {
            status = CFG_YELLOW;
            temp_duration = time_yellow;
            blink_on = 0;
            traffic_light_init();
            setTimer(1, 250);
            update_lcd_display();
        }
        else if (systemMode == 4)
        {
            status = CFG_GREEN;
            temp_duration = time_green;
            blink_on = 0;
            traffic_light_init();
            setTimer(1, 250);
            update_lcd_display();
        }
        else if (systemMode == 5)
        {
            // Khi từ Auto/Config vào Manual: Nếu trước đó đang ở nhánh Trục 1 Xanh thì giữ Trục 1 Xanh,
            // ngược lại đưa về mặc định an toàn Trục 1 Đỏ - Trục 2 Xanh
            if (traffic_state == TRAFFIC_GREEN_RED || traffic_state == TRAFFIC_YELLOW_RED)
            {
                status = MAN_GREEN_RED;
                traffic_set(1, LIGHT_GREEN);
                traffic_set(2, LIGHT_RED);
            }
            else
            {
                status = MAN_RED_GREEN;
                traffic_set(1, LIGHT_RED);
                traffic_set(2, LIGHT_GREEN);
            }
            traffic_state = TRAFFIC_INIT;
            update_lcd_display();
        }
    }

    // 2. XỬ LÝ MÁY TRẠNG THÁI THEO TỪNG CHẾ ĐỘ
    switch (systemMode)
    {

    // ====================================================================
    // Chế độ 1: Hoạt động bình thường (Tự động)
    // ====================================================================
    case 1: // MODE_1_NORMAL
        switch (traffic_state)
        {
        case TRAFFIC_INIT:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);
            count_road1 = time_red;
            count_road2 = time_green;
            status = AUTO_RED_GREEN;
            traffic_state = TRAFFIC_RED_GREEN;

            update_lcd_display();
            setTimer(0, 1000);
            break;

        case TRAFFIC_RED_GREEN:
            if (timer_flag[0] == 1)
            {
                count_road1--;
                count_road2--;
                if (count_road2 <= 0)
                {
                    count_road2 = time_yellow;
                    traffic_set(2, LIGHT_AMBER);
                    status = AUTO_RED_YELLOW;
                    traffic_state = TRAFFIC_RED_YELLOW;
                }
                update_lcd_display();
                setTimer(0, 1000);
            }
            break;

        case TRAFFIC_RED_YELLOW:
            if (timer_flag[0] == 1)
            {
                count_road1--;
                count_road2--;
                if (count_road2 <= 0)
                {
                    count_road1 = time_green;
                    count_road2 = time_red;
                    traffic_set(1, LIGHT_GREEN);
                    traffic_set(2, LIGHT_RED);
                    status = AUTO_GREEN_RED;
                    traffic_state = TRAFFIC_GREEN_RED;
                }
                update_lcd_display();
                setTimer(0, 1000);
            }
            break;

        case TRAFFIC_GREEN_RED:
            if (timer_flag[0] == 1)
            {
                count_road1--;
                count_road2--;
                if (count_road1 <= 0)
                {
                    count_road1 = time_yellow;
                    traffic_set(1, LIGHT_AMBER);
                    status = AUTO_YELLOW_RED;
                    traffic_state = TRAFFIC_YELLOW_RED;
                }
                update_lcd_display();
                setTimer(0, 1000);
            }
            break;

        case TRAFFIC_YELLOW_RED:
            if (timer_flag[0] == 1)
            {
                count_road1--;
                count_road2--;
                if (count_road1 <= 0)
                {
                    count_road1 = time_red;
                    count_road2 = time_green;
                    traffic_set(1, LIGHT_RED);
                    traffic_set(2, LIGHT_GREEN);
                    status = AUTO_RED_GREEN;
                    traffic_state = TRAFFIC_RED_GREEN;
                }
                update_lcd_display();
                setTimer(0, 1000);
            }
            break;
        }
        break;

    // ====================================================================
    // Chế độ 2: Điều chỉnh thời gian cho RED
    // ====================================================================
    case 2: // MODE_2_RED
        traffic_state = TRAFFIC_INIT;

        if (timer_flag[1] == 1)
        {
            blink_on = !blink_on;
            traffic_set(1, blink_on ? LIGHT_RED : LIGHT_OFF);
            traffic_set(2, blink_on ? LIGHT_RED : LIGHT_OFF);
            setTimer(1, 250);
        }

        // Nút 2 (index 1): Tăng thời gian (hỗ trợ cả nhấn nhả và nhấn giữ 1s)
        if (is_button_pressed(1) || is_button_pressed_1s(1))
        {
            temp_duration++;
            if (temp_duration > 99)
                temp_duration = 1;
            update_lcd_display();
        }

        // Nút 3 (index 2): Giảm thời gian
        if (is_button_pressed(2) || is_button_pressed_1s(2))
        {
            temp_duration--;
            if (temp_duration < 1)
                temp_duration = 99;
            update_lcd_display();
        }

        // Nút 4 (index 3): Xác nhận lưu (Đảm bảo T_Red > T_Yellow)
        if (is_button_pressed(3))
        {
            if (temp_duration > time_yellow)
            {
                time_red = temp_duration;
                time_green = time_red - time_yellow;
            }
            update_lcd_display();
        }
        break;

    // ====================================================================
    // Chế độ 3: Điều chỉnh thời gian cho YELLOW
    // ====================================================================
    case 3: // MODE_3_YELLOW
        traffic_state = TRAFFIC_INIT;

        if (timer_flag[1] == 1)
        {
            blink_on = !blink_on;
            traffic_set(1, blink_on ? LIGHT_AMBER : LIGHT_OFF);
            traffic_set(2, blink_on ? LIGHT_AMBER : LIGHT_OFF);
            setTimer(1, 250);
        }

        // Nút 2 (index 1): Tăng thời gian
        if (is_button_pressed(1) || is_button_pressed_1s(1))
        {
            temp_duration++;
            if (temp_duration > 99)
                temp_duration = 1;
            update_lcd_display();
        }

        // Nút 3 (index 2): Giảm thời gian
        if (is_button_pressed(2) || is_button_pressed_1s(2))
        {
            temp_duration--;
            if (temp_duration < 1)
                temp_duration = 99;
            update_lcd_display();
        }

        // Nút 4 (index 3): Xác nhận lưu
        if (is_button_pressed(3))
        {
            time_yellow = temp_duration;
            time_red = time_green + time_yellow;
            update_lcd_display();
        }
        break;

    // ====================================================================
    // Chế độ 4: Điều chỉnh thời gian cho GREEN
    // ====================================================================
    case 4: // MODE_4_GREEN
        traffic_state = TRAFFIC_INIT;

        if (timer_flag[1] == 1)
        {
            blink_on = !blink_on;
            traffic_set(1, blink_on ? LIGHT_GREEN : LIGHT_OFF);
            traffic_set(2, blink_on ? LIGHT_GREEN : LIGHT_OFF);
            setTimer(1, 250);
        }

        // Nút 2 (index 1): Tăng thời gian
        if (is_button_pressed(1) || is_button_pressed_1s(1))
        {
            temp_duration++;
            if (temp_duration > 99)
                temp_duration = 1;
            update_lcd_display();
        }

        // Nút 3 (index 2): Giảm thời gian
        if (is_button_pressed(2) || is_button_pressed_1s(2))
        {
            temp_duration--;
            if (temp_duration < 1)
                temp_duration = 99;
            update_lcd_display();
        }

        // Nút 4 (index 3): Xác nhận lưu
        if (is_button_pressed(3))
        {
            time_green = temp_duration;
            time_red = time_green + time_yellow;
            update_lcd_display();
        }
        break;

    // ====================================================================
    // Chế độ 5: Điều khiển bằng tay (Manual - Có tự động chờ đèn Vàng)
    // ====================================================================
    case 5: // MODE_5_MANUAL
        traffic_state = TRAFFIC_INIT;

        switch (status)
        {
        case MAN_RED_GREEN:
            // Đang Đỏ 1 - Xanh 2: Nếu nhấn Nút 2 (index 1) -> Chuyển sang Đỏ 1 - Vàng 2
            if (is_button_pressed(1))
            {
                status = MAN_RED_YELLOW;
                count_road2 = time_yellow; // Nạp số giây chờ đèn Vàng
                traffic_set(1, LIGHT_RED);
                traffic_set(2, LIGHT_AMBER);
                update_lcd_display();
                setTimer(0, 1000); // Bắt đầu đếm ngược từng giây cho đèn Vàng
            }
            break;

        case MAN_RED_YELLOW:
            // Tự động đếm ngược hết thời gian đèn Vàng rồi mới bật Xanh 1 - Đỏ 2
            if (timer_flag[0] == 1)
            {
                count_road2--;
                if (count_road2 <= 0)
                {
                    status = MAN_GREEN_RED;
                    traffic_set(1, LIGHT_GREEN);
                    traffic_set(2, LIGHT_RED);
                    update_lcd_display();
                }
                else
                {
                    update_lcd_display();
                    setTimer(0, 1000);
                }
            }
            break;

        case MAN_GREEN_RED:
            // Đang Xanh 1 - Đỏ 2: Nếu nhấn Nút 2 (index 1) -> Chuyển sang Vàng 1 - Đỏ 2
            if (is_button_pressed(1))
            {
                status = MAN_YELLOW_RED;
                count_road1 = time_yellow; // Nạp số giây chờ đèn Vàng
                traffic_set(1, LIGHT_AMBER);
                traffic_set(2, LIGHT_RED);
                update_lcd_display();
                setTimer(0, 1000); // Bắt đầu đếm ngược từng giây cho đèn Vàng
            }
            break;

        case MAN_YELLOW_RED:
            // Tự động đếm ngược hết thời gian đèn Vàng rồi mới bật Đỏ 1 - Xanh 2
            if (timer_flag[0] == 1)
            {
                count_road1--;
                if (count_road1 <= 0)
                {
                    status = MAN_RED_GREEN;
                    traffic_set(1, LIGHT_RED);
                    traffic_set(2, LIGHT_GREEN);
                    update_lcd_display();
                }
                else
                {
                    update_lcd_display();
                    setTimer(0, 1000);
                }
            }
            break;

        default:
            status = MAN_RED_GREEN;
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);
            update_lcd_display();
            break;
        }
        break;

    default:
        systemMode = 1;
        break;
    }
}
