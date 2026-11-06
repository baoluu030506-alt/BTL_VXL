#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

//SYSTEM PARAMETERS
#define TICK_MS                 10          // Chu kỳ ngắt Timer (10ms)

//HARDWARE ADDRESSES
#define LCD_I2C_ADDR            (0x21 << 1) // Địa chỉ LCD đã quét (0x21)
#define DHT20_I2C_ADDR          (0x38 << 1) // Địa chỉ DHT20 đã quét (0x38)

//FSM STATES
#define INIT                    0

// Chế độ Tự động (Auto)
#define AUTO_RED_GREEN          1
#define AUTO_RED_YELLOW         2
#define AUTO_GREEN_RED          3
#define AUTO_YELLOW_RED         4

// Chế độ Chỉnh tay (Manual)
#define MAN_RED_GREEN           11
#define MAN_RED_YELLOW          12
#define MAN_GREEN_RED           13
#define MAN_YELLOW_RED          14

// Chế độ Cài đặt (Config/Tuning)
#define CFG_RED                 21
#define CFG_YELLOW              22
#define CFG_GREEN               23

//GLOBAL VARIABLES
extern int status;          // Trạng thái hiện tại của hệ thống

extern int time_red;        // Thời gian cài đặt cho đèn Đỏ
extern int time_yellow;     // Thời gian cài đặt cho đèn Vàng
extern int time_green;      // Thời gian cài đặt cho đèn Xanh

extern int count_road1;     // Biến đếm ngược hiển thị cho Trục 1
extern int count_road2;     // Biến đếm ngược hiển thị cho Trục 2

#endif /* INC_GLOBAL_H_ */
