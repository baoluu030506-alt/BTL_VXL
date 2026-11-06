#include "scheduler.h"

//LOCAL VARIABLES
static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint8_t current_index_task = 0;

//FUNCTION IMPLEMENTATIONS
void SCH_Init(void) {
    // Khởi tạo mảng task rỗng
}

uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD) {
    // Thuật toán chèn vào danh sách theo Delta Delay
    return 0;
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    // Xóa task và cộng dồn Delay cho task phía sau
    return 0;
}

void SCH_Update(void) {
    // Xử lý giảm Delay của phần tử đầu tiên (O(1))
}

void SCH_Dispatch_Tasks(void) {
    // Kiểm tra RunMe phần tử đầu tiên và thực thi
}
