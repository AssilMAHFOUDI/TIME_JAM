#include "player_action.h"
#include <stdio.h>
 
int move(char *buffer, int number_ship, int angle, int speed) {
    if (number_ship < 1 || number_ship > 9)
        return 1; // erreur id invalide
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide
    if (speed < 0 || speed > 3000)
        return 3; // erreur vitesse invalide
 
    sprintf(buffer, "MOVE %d %d %d", number_ship, angle, speed);
    return 0;
}
 
int fire(char *buffer, int ship_id, int angle) {
    if (ship_id < 1 || ship_id > 5)
        return 1; // erreur : pas un attaquant
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide
 
    sprintf(buffer, "FIRE %d %d", ship_id, angle);
    return 0;
}
 
int radar(char *buffer, int ship_id) {
    if (ship_id != 6 && ship_id != 7)
        return 1; // erreur : pas un explorateur
 
    sprintf(buffer, "RADAR %d", ship_id);
    return 0;
}
 