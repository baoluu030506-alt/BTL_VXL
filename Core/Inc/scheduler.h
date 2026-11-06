#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"

#define SCH_MAX_TASKS 10

// Cấu trúc dữ liệu Task
typedef struct {
    void (*pTask)(void);    // Con trỏ tới hàm task
    uint32_t Delay;         // Số tick còn lại (tương đối)
    uint32_t Period;        // Chu kỳ lặp lại (0 = one-shot task)
    uint8_t RunMe;          // Cờ báo task sẵn sàng chạy
    uint32_t TaskID;        // Định danh task
} sTask;

//FUNCTION PROTOTYPES
void SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);

void SCH_Update(void);          // Hàm xử lý O(1), gọi trong ngắt TIM2
void SCH_Dispatch_Tasks(void);  // Hàm thực thi, gọi trong while(1)

#endif /* INC_SCHEDULER_H_ */
