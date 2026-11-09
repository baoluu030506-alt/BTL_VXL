#include "scheduler.h"

//LOCAL VARIABLES
static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint8_t current_index_task = 0;

//FUNCTION IMPLEMENTATIONS
static inline uint32_t SCH_Lock(void) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    return primask;
}

static inline void SCH_Unlock(uint32_t primask) {
    __set_PRIMASK(primask);
}

static uint32_t Insert(void (*pFunc)(void), uint32_t delay, uint32_t period, uint32_t id){
    uint32_t m = SCH_Lock();

    if(current_index_task >= SCH_MAX_TASKS){
        SCH_Unlock(m);
        return 0;
    }
    uint8_t idx = 0;
    uint32_t sum = 0;

    while (idx < current_index_task && sum + SCH_tasks_G[idx].Delay <= delay) {
        sum += SCH_tasks_G[idx++].Delay;
    }

    for (uint8_t i = current_index_task; i > idx; i--) {
        SCH_tasks_G[i] = SCH_tasks_G[i - 1];
    }

    SCH_tasks_G[idx].pTask = pFunc;
    SCH_tasks_G[idx].Delay = delay - sum;
    SCH_tasks_G[idx].Period = period;
    SCH_tasks_G[idx].TaskID = id;
    SCH_tasks_G[idx].RunMe = (idx == 0 && SCH_tasks_G[idx].Delay == 0);

    if (idx < current_index_task) {
        SCH_tasks_G[idx + 1].Delay -= SCH_tasks_G[idx].Delay;
    }

    current_index_task++;
    SCH_Unlock(m);
    return id;
}
void SCH_Init(void) {
    // Khởi tạo mảng task rỗng
    uint32_t m = SCH_Lock();
    current_index_task = 0;
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
    SCH_Unlock(m);
}

uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD) {
    // Thuật toán chèn vào danh sách theo Delta Delay
    static uint32_t next_id = 1;
    return Insert(pFunc, DELAY, PERIOD, next_id++);
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    // Xóa task và cộng dồn Delay cho task phía sau
    uint32_t m = SCH_Lock();
    uint8_t found = 0;

    for (uint8_t i = 0; i < current_index_task; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {
            found = 1;
            
            // Bàn giao Delay
            if (i + 1 < current_index_task) {
                SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;
                SCH_tasks_G[i + 1].RunMe = (i == 0 && SCH_tasks_G[i + 1].Delay == 0);
            }
            
            // Dịch mảng lên
            for (uint8_t j = i; j + 1 < current_index_task; j++) {
                SCH_tasks_G[j] = SCH_tasks_G[j + 1];
            }
            
            current_index_task--;
            break;
        }
    } 
    SCH_Unlock(m);
    return found;
}

void SCH_Update(void) {
    // Xử lý giảm Delay của phần tử đầu tiên (O(1))
    if (current_index_task == 0) return;
    
    if (SCH_tasks_G[0].Delay > 0) {
        SCH_tasks_G[0].Delay--;
    }
    
    if (SCH_tasks_G[0].Delay == 0) {
        SCH_tasks_G[0].RunMe = 1;
    }
}

void SCH_Dispatch_Tasks(void) {
    // Kiểm tra RunMe phần tử đầu tiên và thực thi
    while(current_index_task > 0 && SCH_tasks_G[0].RunMe){
        sTask t = SCH_tasks_G[0];

        t.pTask();

        if (SCH_Delete_Task(t.TaskID) && t.Period > 0) {
            Insert(t.pTask, t.Period, t.Period, t.TaskID);
        }
    }
}
