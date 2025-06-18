#include "player_action.h"
#include <stdio.h>
char* move(int number_sheep, int angle, int speed)
{
    static char buffer[50]; // buffer statique pour conserver la chaîne après la fin de la fonction
    sprintf(buffer, "MOVE %d %d %d", number_sheep, angle, speed);
    return buffer;
}
