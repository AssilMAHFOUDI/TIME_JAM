#include "player_action.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
 
int move(char *buffer, int number_ship, int angle, int speed) {
    if (number_ship < 1 || number_ship > 9)
        return 1; // erreur id invalide
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide
    if (speed < 0 || speed > 3000)
        return 3; // erreur vitesse invalide
 
    sprintf(buffer, "MOVE %d %d %d\n", number_ship, angle, speed);
    return 0;
}
 
int fire(char *buffer, int ship_id, int angle) {
    if (ship_id < 1 || ship_id > 5)
        return 1; // erreur : pas un attaquant
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide
 
    sprintf(buffer, "FIRE %d %d\n", ship_id, angle);
    return 0;
}
 
int radar(char *buffer, int ship_id) {
    if (ship_id != 6 && ship_id != 7)
        return 1; // erreur : pas un explorateur
 
    sprintf(buffer, "RADAR %d\n", ship_id);
    return 0;
}

void parse_radar_response(const char *input, RadarInfo *info) {
    info->planet_count = 0;
    info->ship_count = 0;
    info->base.x = 0;
    info->base.y = 0;

    char buffer[256];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ",");

    while (token != NULL) {
        if (token[0] == 'P') {
            Planet *planet = &info->planets[info->planet_count];
            int ret = sscanf(token, "P %d %d %d %d %d",
                             &planet->planet_id,
                             &planet->x,
                             &planet->y,
                             &planet->collected_by,
                             &planet->at_base);
            if (ret == 5)
                info->planet_count++;
        } else if (token[0] == 'S') {
            Ship *ship = &info->ships[info->ship_count];
            int ret = sscanf(token, "S %d %d %d %d %d",
                             &ship->team,
                             &ship->ship_id,
                             &ship->x,
                             &ship->y,
                             &ship->broken);
            if (ret == 5)
                info->ship_count++;
        } else if (token[0] == 'B') {
            int x, y;
            int ret = sscanf(token, "B %d %d", &x, &y);
            if (ret == 2) {
                info->base.x = x;
                info->base.y = y;
            }
        }
        token = strtok(NULL, ",");
    }
}

//  Fonction pour calculer l’angle
int calculate_angle(int x1, int y1, int x2, int y2) {
    double angle_rad = atan2(y2 - y1, x2 - x1);
    int angle_deg = (int)(angle_rad * 180 / M_PI);
    if (angle_deg < 0)
        angle_deg += 360;
    return angle_deg;

}