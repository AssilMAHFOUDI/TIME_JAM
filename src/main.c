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
    int idx_angle=0;
    gets(buffer);
    while (1)
    {
    idx_angle+=1;


        fire(buffer, 5, (((4+idx_angle)%8)*45));
        puts(buffer);
        gets(buffer);

        fire(buffer, 3, (((3+idx_angle)%8)*45));
        puts(buffer);
        gets(buffer);

        fire(buffer, 2, (((2+idx_angle)%8)*45));
        puts(buffer);
        gets(buffer);


        fire(buffer, 4, (((4+idx_angle)%8)*45));
        puts(buffer);
        gets(buffer);


        fire(buffer, 1, (((1+idx_angle)%8)*45));
        puts(buffer);
        gets(buffer);

        
        radar(buffer, 7);
        puts(buffer);
        // puts("RADAR 7\n");
        gets(buffer);


    Radar radar_instance;
    radar_instance.radar_id= 7; // ID du radar_instance
    radar_instance.planet_count = 0;
    radar_instance.ship_count = 0;
    int huit=0;
    int neuf=0;
    int huit_vasy=40;

    int huit_neuf[2]= {0, 0}; // Pour stocker les indices des planètes associées aux vaisseaux 8 et 9

    parse_radar_data(&radar_instance, buffer);
    
    reorder_planets(&radar_instance);
    


    for(int ship_index=8;ship_index<10;ship_index++)
    {
        if((radar_instance.ships[ship_index-1].broken==1))
        {
           huit_neuf[ship_index-8]==99; 
           go_base(ship_index, &radar_instance, buffer);
              continue; // Si le vaisseau est cassé, on passe au suivant
        }

       for(int planet_index = 0; planet_index < radar_instance.planet_count; planet_index++) {
            if ((radar_instance.planets[planet_index].ship_id == ship_index)&&(radar_instance.planets[planet_index].saved!=1)) {
                huit_neuf[ship_index-8] = 1;
                // Calculer l'angle entre le vaisseau et la planète
                go_base(ship_index, &radar_instance, buffer);
            }
        }
    }
    for(int ship_index=8;ship_index<10;ship_index++)
    {


        if((radar_instance.ships[ship_index-1].broken==1))
        {
           huit_neuf[ship_index-8]==99; 
           go_base(ship_index, &radar_instance, buffer);
           
        continue; // Si le vaisseau est cassé, on passe au suivant
        }
        if(huit_neuf[ship_index-8]==0) // Si la planète associée au vaisseau 8 ou 9 n'a pas été trouvée
        {
            for(int planet_index = 0; planet_index < radar_instance.planet_count; planet_index++) {
                if ((radar_instance.planets[planet_index].ship_id == -1)&&(radar_instance.planets[planet_index].saved==0)) {

                    go_planet(ship_index, planet_index, &radar_instance, buffer); // Déplacer le vaisseau vers la planète
                    
                    huit_neuf[ship_index-8] = planet_index; // Marquer la planète associée au vaisseau 8 ou 9 comme trouvée

                    break; // Sortir de la boucle une fois que le vaisseau a été déplacé vers une planète
                }
            }
        }
    }


    for(int ship_index=1;ship_index<6;ship_index++)
    {
        if((radar_instance.ships[ship_index-1].broken==1))
        {
           huit_neuf[ship_index-8]==99; 
           go_base(ship_index, &radar_instance, buffer);
              continue; // Si le vaisseau est cassé, on passe au suivant
        }

        int idx_colector= 8+ (ship_index%2); // Indice du vaisseau 8, 9, 10, 11, 12

        int angle = calculate_angle(radar_instance.ships[ship_index-1].abscissa, radar_instance.ships[ship_index-1].ordinate,radar_instance.ships[idx_colector-1].abscissa, radar_instance.ships[idx_colector-1].ordinate);
        move(buffer, ship_index, angle, 3000);
        puts(buffer);
        gets(buffer);
                
    }


    }
}
