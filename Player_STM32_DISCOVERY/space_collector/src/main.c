#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"

osThreadId_t defaultTaskHandle;

void StartDefaultTask(void *argument);

int main(void)
{
    hardware_init();

    osKernelInitialize();

    const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 128,
    };
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    osKernelStart();

    while (1)
    {
    }
}

void StartDefaultTask(void *argument)
{
    while (1)
    {
        puts("MOVE 1 0 1000\n");
        osDelay(1000);
    }
}
