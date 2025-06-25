#include "player_action.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif



// // Custom function to convert integer to string
void int_to_string(char *dest, int num) {
    if (num == 0) {
        dest[0] = '0';
        dest[1] = '\0';
        return;
    }
    int is_negative = num < 0;
    if (is_negative) num = -num;
    char temp[12]; // Enough for 32-bit int (-2147483648)
    int i = 0;
    while (num > 0) {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }
    if (is_negative) temp[i++] = '-';
    int j = 0;
    while (i > 0) dest[j++] = temp[--i];
    dest[j] = '\0';
}

// Custom function to concatenate strings and numbers
void string_concat(char *dest, const char *str1, int num1, const char *str2, int num2, const char *str3, int num3, const char *end) {
    int i = 0;
    // Copy str1
    while (str1 && str1[i]) {
        dest[i] = str1[i];
        i++;
    }
    // Convert and append num1
    if (num1 >= 0) {
        char num_str[12];
        int_to_string(num_str, num1);
        int j = 0;
        while (num_str[j]) dest[i++] = num_str[j++];
    }
    // Copy str2
    if (str2) {
        int j = 0;
        while (str2[j]) dest[i++] = str2[j++];
    }
    // Convert and append num2
    if (num2 >= 0) {
        char num_str[12];
        int_to_string(num_str, num2);
        int j = 0;
        while (num_str[j]) dest[i++] = num_str[j++];
    }
    // Copy str3
    if (str3) {
        int j = 0;
        while (str3[j]) dest[i++] = str3[j++];
    }
    // Convert and append num3
    if (num3 >= 0) {
        char num_str[12];
        int_to_string(num_str, num3);
        int j = 0;
        while (num_str[j]) dest[i++] = num_str[j++];
    }
    // Copy end
    int j = 0;
    while (end[j]) dest[i++] = end[j++];
    dest[i] = '\0';
}

// // Custom function to convert string to integer
// int string_to_int(const char *str) {
//     int result = 0;
//     int sign = 1;
//     int i = 0;
//     if (str[0] == '-') {
//         sign = -1;
//         i++;
//     }
//     while (str[i] >= '0' && str[i] <= '9') {
//         result = result * 10 + (str[i] - '0');
//         i++;
//     }
//     return sign * result;
// }

// // Custom function to parse space-separated numbers
// void parse_numbers(const char *token, int *values, int max_values) {
//     int count = 0;
//     int i = 0, start = 0;
//     char num_str[12];
//     while (token[i] && count < max_values) {
//         if (token[i] == ' ' || token[i] == '\0') {
//             if (i > start) {
//                 int j;
//                 for (j = 0; j < i - start; j++) num_str[j] = token[start + j];
//                 num_str[j] = '\0';
//                 values[count++] = string_to_int(num_str);
//                 start = i + 1;
//             }
//         }
//         if (token[i] == '\0') break;
//         i++;
//     }
//     // Handle last number if no trailing space
//     if (i > start && count < max_values) {
//         int j;
//         for (j = 0; j < i - start; j++) num_str[j] = token[start + j];
//         num_str[j] = '\0';
//         values[count++] = string_to_int(num_str);
//     }
// }




int move(char *buffer, int number_ship, int angle, int speed) {
    if (number_ship < 1 || number_ship > 9)
        return 1; // erreur id invalide
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide
    if (speed < 0 || speed > 3000)
        return 3; // erreur vitesse invalide

    string_concat(buffer, "MOVE ", number_ship, " ", angle, " ", speed, "\n");
    return 0;
}

int fire(char *buffer, int ship_id, int angle) {
    if (ship_id < 1 || ship_id > 5)
        return 1; // erreur : pas un attaquant
    if (angle < 0 || angle >= 360)
        return 2; // erreur angle invalide

    string_concat(buffer, "FIRE ", ship_id, " ", angle, "\n", -1, "");
    return 0;
}

int radar(char *buffer, int ship_id) {
    if (ship_id != 6 && ship_id != 7)
        return 1; // erreur : pas un explorateur

    string_concat(buffer, "RADAR ", ship_id, "\n", -1, "", -1, "");
    return 0;
}
// Calculate angle between two points (uses math.h but no stdio.h)
int calculate_angle(int x1, int y1, int x2, int y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double rad = atan2(dy, dx);
    int deg = (int)(rad * 180.0 / M_PI);
    return (deg < 0) ? deg + 360 : deg;
}

void parse_radar_data(Radar *radar_instance, const char *buffer) {
    radar_instance->planet_count = 0;
    radar_instance->ship_count = 0;
    
    // Parser les données
    const char *current_line = buffer;
    while (current_line[0] != '\0') {
        if (current_line[0] == 'P') {
            // Parser une planète
            radar_instance->planets[radar_instance->planet_count].type = current_line[0];
            const char *current = current_line;

            char *space1 = strchr(current, ' ');
            current = space1 + 1;
            radar_instance->planets[radar_instance->planet_count].planet_id = atoi(current);

            char *space2 = strchr(current, ' ');
            current = space2 + 1;
            radar_instance->planets[radar_instance->planet_count].abscissa = atoi(current);

            char *space3 = strchr(current, ' ');
            current = space3 + 1;
            radar_instance->planets[radar_instance->planet_count].ordinate = atoi(current);

            char *space4 = strchr(current, ' ');
            current = space4 + 1;
            radar_instance->planets[radar_instance->planet_count].ship_id = atoi(current);

            char *space5 = strchr(current, ' ');
            current = space5 + 1;
            radar_instance->planets[radar_instance->planet_count].saved = atoi(current);

            radar_instance->planet_count++;
        }
        else if (current_line[0] == 'S') {
            // Parser un vaisseau
            radar_instance->ships[radar_instance->ship_count].type = current_line[0];
            const char *current = current_line;

            char *space1 = strchr(current, ' ');
            current = space1 + 1;
            radar_instance->ships[radar_instance->ship_count].team = atoi(current);

            char *space2 = strchr(current, ' ');
            current = space2 + 1;
            radar_instance->ships[radar_instance->ship_count].ship_id = atoi(current);

            char *space3 = strchr(current, ' ');
            current = space3 + 1;
            radar_instance->ships[radar_instance->ship_count].abscissa = atoi(current);

            char *space4 = strchr(current, ' ');
            current = space4 + 1;
            radar_instance->ships[radar_instance->ship_count].ordinate = atoi(current);

            char *space5 = strchr(current, ' ');
            current = space5 + 1;
            radar_instance->ships[radar_instance->ship_count].broken = atoi(current);

            radar_instance->ship_count++;
        }
        else if (current_line[0] == 'B') {
            // Parser la base
            radar_instance->base.type = current_line[0];
            const char *current = current_line;

            char *space1 = strchr(current, ' ');
            current = space1 + 1;
            radar_instance->base.abscissa = atoi(current);

            char *space2 = strchr(current, ' ');
            current = space2 + 1;
            radar_instance->base.ordinate = atoi(current);
        }

        // Passer à la ligne suivante
        char *comma = strchr(current_line, ',');
        if (comma == NULL) break;
        current_line = comma + 1;
    }
}
void go_base(int ship_id, Radar *radar_instance, char *buffer)
{
    int angle_b = calculate_angle(radar_instance->ships[ship_id-1].abscissa, radar_instance->ships[ship_id-1].ordinate, radar_instance->base.abscissa, radar_instance->base.ordinate);
                           // Générer la commande MOVE
    move(buffer, ship_id, angle_b, 1000);
    puts(buffer);
    gets(buffer);
}

void go_planet(int ship_id, int planet_index, Radar *radar_instance, char *buffer)
{
    int angle = calculate_angle(radar_instance->ships[ship_id-1].abscissa, radar_instance->ships[ship_id-1].ordinate, radar_instance->planets[planet_index].abscissa, radar_instance->planets[planet_index].ordinate);
    move(buffer, ship_id, angle, 1000);
    puts(buffer);
    gets(buffer);

}

void reorder_planets(Radar *radar_instance)
{
    // Réorganiser les planètes en fonction de leur distance à la base
    for (int i = 0; i < radar_instance->planet_count - 1; i++) {
        for (int j = i + 1; j < radar_instance->planet_count; j++) {
            int dist_i = (radar_instance->planets[i].abscissa - radar_instance->base.abscissa) * (radar_instance->planets[i].abscissa - radar_instance->base.abscissa) +
                         (radar_instance->planets[i].ordinate - radar_instance->base.ordinate) * (radar_instance->planets[i].ordinate - radar_instance->base.ordinate);
            int dist_j = (radar_instance->planets[j].abscissa - radar_instance->base.abscissa) * (radar_instance->planets[j].abscissa - radar_instance->base.abscissa) +
                         (radar_instance->planets[j].ordinate - radar_instance->base.ordinate) * (radar_instance->planets[j].ordinate - radar_instance->base.ordinate);
            if (dist_i > dist_j) {
                Planet temp = radar_instance->planets[i];
                radar_instance->planets[i] = radar_instance->planets[j];
                radar_instance->planets[j] = temp;
            }
        }
    }
}










