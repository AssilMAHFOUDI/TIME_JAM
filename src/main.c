#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"
#include "player_action.h"

osThreadId_t defaultTaskHandle;

void StartDefaultTask(void *argument);

int main(void)
{
    hardware_init();

    osKernelInitialize();

    const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2500,
    };
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    osKernelStart();

    while (1)
    {
    }
}

void StartDefaultTask(void *argument)

{
    char buffer[500];
    gets(buffer);
    while (1)
    {
        // char* buffer[50];
        // char buffer[500];
        // gets(buffer);
        move(buffer, 8, 70, 1000);
        puts(buffer);
        gets(buffer);
        
        // osDelay(100);
        move(buffer, 3, 80, 1000);
        puts(buffer);
        
        gets(buffer);


        fire(buffer, 3, 90);
        puts(buffer);
        gets(buffer);

        
        radar(buffer, 7);
        puts(buffer);
        // puts("RADAR 7\n");
        gets(buffer);

        // fire(buffer, 3, 90);
        // puts(buffer);
        // gets(buffer);
    }
}
