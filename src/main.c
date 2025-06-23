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
    char buffer[1000];
    gets(buffer);
    int x=2 ;
    while (1)
    {
    char buffer[1000];
              // // char* buffer[50];
        // // char buffer[500];
        // // gets(buffer);
        // move(buffer, 8, 70, 1000);
        // puts(buffer);
        // gets(buffer);
        
        // // osDelay(100);
        // move(buffer, 3, 80, 1000);
        // puts(buffer);
        
        // gets(buffer);


        fire(buffer, 3, 90);
        puts(buffer);
        gets(buffer);

        
        radar(buffer, 7);
        puts(buffer);
        // puts("RADAR 7\n");
        gets(buffer);
        parseRadarData(buffer, &radar);
         

        move(buffer, 3, 80, 1000);
        puts(buffer);
        
        gets(buffer);

        // // fire(buffer, 3, 90);
        // // puts(buffer);
        // gets(buffer);
        
        RadarInfo radar;
        move(buffer, 3, 40, 1000);
        puts(buffer);
        
        gets(buffer);
       
        // osDelay(100);

        // Ship ship = radar.ships[0];
        // Planet planet = radar.planets[0];

        // int dx = planet.x - ship.x;
        // int dy = planet.y - ship.y;

        // double angle_rad = atan2(dy, dx);
        // int angle_deg = (int)(angle_rad * 180.0 / M_PI);
        // if (angle_deg < 0) angle_deg += 360;

       

        // move(buffer, ship.ship_id, angle_deg, 1000);
        // string_concat(buffer, "ship_id ", ship.ship_id, " ", angle_deg, "\n", -1, "");
        // puts(ship.ship_id);
        // puts(buffer);
        // gets(buffer);
 
    }
}
