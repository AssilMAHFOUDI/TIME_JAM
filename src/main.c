#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"
#include "player_action.h"
#include <string.h>
#include <stdlib.h>





osThreadId_t defaultTaskHandle;

void StartDefaultTask(void *argument);
char buffer[1000];
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
    // char buffer[1000];
    gets(buffer);
    while (1)
    {
    
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


    
    //     // Tableaux statiques et instance unique
    // Planet planets[20];
    // int planet_count = 0;
    // Ship ships[10];
    // int ship_count = 0;
    // Base base;

    Radar radar_instance;
    radar_instance.radar_id= 7; // ID du radar_instance
    radar_instance.planet_count = 0;
    radar_instance.ship_count = 0;
    int huit=0;
    int neuf=0;
    int huit_vasy=40;

    parse_radar_data(&radar_instance, buffer);
    for(int i = 0; i < radar_instance.planet_count; i++) {
        

        if((radar_instance.planets[i].ship_id!=-1)&&(radar_instance.planets[i].saved!=1))
        {
            if(radar_instance.planets[i].ship_id==8)
            {
                huit=1;
            }
            else if(radar_instance.planets[i].ship_id==9)
            {
                neuf=1;
            }
            int this_ship_id = radar_instance.planets[i].ship_id;
            int angle_b = calculate_angle(radar_instance.ships[this_ship_id-1].abscissa, radar_instance.ships[this_ship_id-1].ordinate, radar_instance.base.abscissa, radar_instance.base.ordinate);
            move(buffer, this_ship_id, angle_b, 1000);
            puts(buffer);
            gets(buffer);
            
            if((huit+neuf)==2)
            {
                continue;
            }

            // int angle = calculate_angle(radar_instance.ships[this_ship_id].abscissa, radar_instance.ships[this_ship_id].ordinate, radar_instance.planets[i].abscissa, radar_instance.planets[i].ordinate);
            // int angle=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.planets[0].abscissa, radar_instance.planets[0].ordinate);
        }
        
    }
    if (huit==0)
    {
        for(int i = 0; i < radar_instance.planet_count; i++) {
        

        if((radar_instance.planets[i].ship_id==-1)&&(radar_instance.planets[i].saved==0))
        {
            // int this_ship_id = radar_instance.planets[i].ship_id;
            // int angle_b = calculate_angle(radar_instance.ships[this_ship_id].abscissa, radar_instance.ships[this_ship_id].ordinate, radar_instance.base.abscissa, radar_instance.base.ordinate);
            int angle = calculate_angle(radar_instance.ships[(8-1)].abscissa, radar_instance.ships[(8-1)].ordinate, radar_instance.planets[i].abscissa, radar_instance.planets[i].ordinate);
            move(buffer, 8, angle, 1000);
            puts(buffer);
            gets(buffer);
            huit_vasy=i;
            break;

            // int angle = calculate_angle(radar_instance.ships[this_ship_id].abscissa, radar_instance.ships[this_ship_id].ordinate, radar_instance.planets[i].abscissa, radar_instance.planets[i].ordinate);
            // int angle=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.planets[0].abscissa, radar_instance.planets[0].ordinate);
        }
        
    }
    }

    if (neuf==0)
    {
        for(int i = huit_vasy+1; i < radar_instance.planet_count; i++) {

        if((radar_instance.planets[i].ship_id==-1)&&(radar_instance.planets[i].saved==0))
        {
            // int this_ship_id = radar_instance.planets[i].ship_id;
            // int angle_b = calculate_angle(radar_instance.ships[this_ship_id].abscissa, radar_instance.ships[this_ship_id].ordinate, radar_instance.base.abscissa, radar_instance.base.ordinate);
            int angle = calculate_angle(radar_instance.ships[(9-1)].abscissa, radar_instance.ships[(9-1)].ordinate, radar_instance.planets[i].abscissa, radar_instance.planets[i].ordinate);
            move(buffer, 9, angle, 1000);
            puts(buffer);
            gets(buffer);


            break; 

            

            // int angle = calculate_angle(radar_instance.ships[this_ship_id].abscissa, radar_instance.ships[this_ship_id].ordinate, radar_instance.planets[i].abscissa, radar_instance.planets[i].ordinate);
            // int angle=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.planets[0].abscissa, radar_instance.planets[0].ordinate);
        }
        
    }
    }





    


            // if(radar_instance.planets[0].ship_id==9)
            // { 
            //     int angle_b=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.base.abscissa, radar_instance.base.ordinate);
            //     move(buffer, 9, angle_b, 1000);
            //     puts(buffer);
                
            //     gets(buffer);

            // }

            // else if((radar_instance.planets[0].type=='P') && (radar_instance.planets[0].ship_id!=9)){

            //     move(buffer, 9, angle, 1000);
            //     puts(buffer);
                
            //     gets(buffer);
            // }
            // else
            // {
                
            //     move(buffer, 9, 0, 1000);
            //     puts(buffer);
                
            //     gets(buffer);
                
                
            //     move(buffer, 8, 0, 1000);
            //     puts(buffer);
                
            //     gets(buffer);
            // }





















    // int angle=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.planets[0].abscissa, radar_instance.planets[0].ordinate);



    //         if(radar_instance.planets[0].ship_id==9)
    //         { 
    //             int angle_b=calculate_angle(radar_instance.ships[8].abscissa,radar_instance.ships[8].ordinate,radar_instance.base.abscissa, radar_instance.base.ordinate);
    //             move(buffer, 9, angle_b, 1000);
    //             puts(buffer);
                
    //             gets(buffer);

    //         }

    //         else if((radar_instance.planets[0].type=='P') && (radar_instance.planets[0].ship_id!=9)){

    //             move(buffer, 9, angle, 1000);
    //             puts(buffer);
                
    //             gets(buffer);
    //             // valid= 1; // Marquer comme valide si toutes les valeurs sont lues
                
                
    //             // move(buffer, 8, 120, 1000);
    //             // puts(buffer);
                
    //             // gets(buffer);
    //         }
    //         else
    //         {
                
    //             move(buffer, 9, 0, 1000);
    //             puts(buffer);
                
    //             gets(buffer);
                
                
    //             move(buffer, 8, 0, 1000);
    //             puts(buffer);
                
    //             gets(buffer);
    //         }
            

            

           


             

         
    //         // Variables temporaires pour parsing manuel
    //         char *token = strtok(first_line, " ");
    //         int index = 0;
    //         while (token != NULL && index < 6) {
    //             if (index == 0) {
    //                 type = token[0]; // Premier caractère pour type
    //             } else if (index == 1) {
    //                 planet_id = atoi(token);
    //             } else if (index == 2) {
    //                 abscissa = atoi(token);
    //             } else if (index == 3) {
    //                 ordinate = atoi(token);
    //             } else if (index == 4) {
    //                 ship_id = atoi(token);
    //             } else if (index == 5) {
    //                 saved = atoi(token);
    //             }
    //             token = strtok(NULL, " ");
    //             index++;
    //         }
    //         if (index == 6) {
    //             valid = 1; // Marquer comme valide si toutes les valeurs sont lues
    //         }
    //     }
    // }

    // // Libérer la mémoire
    // free(data_copy);



        
         

        // move(buffer, 3, 80, 1000);
        // puts(buffer);
        
        // gets(buffer);

        // // fire(buffer, 3, 90);
        // // puts(buffer);
        // gets(buffer);
    

        // move(buffer, 3, 40, 1000);
        // puts(buffer);
        
        // gets(buffer);
       
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
