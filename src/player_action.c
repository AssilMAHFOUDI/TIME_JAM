#include "player_action.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

// Custom function to convert integer to string
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

// Custom function to convert string to integer
int string_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return sign * result;
}

// Custom function to parse space-separated numbers
void parse_numbers(const char *token, int *values, int max_values) {
    int count = 0;
    int i = 0, start = 0;
    char num_str[12];
    while (token[i] && count < max_values) {
        if (token[i] == ' ' || token[i] == '\0') {
            if (i > start) {
                int j;
                for (j = 0; j < i - start; j++) num_str[j] = token[start + j];
                num_str[j] = '\0';
                values[count++] = string_to_int(num_str);
                start = i + 1;
            }
        }
        if (token[i] == '\0') break;
        i++;
    }
    // Handle last number if no trailing space
    if (i > start && count < max_values) {
        int j;
        for (j = 0; j < i - start; j++) num_str[j] = token[start + j];
        num_str[j] = '\0';
        values[count++] = string_to_int(num_str);
    }
}

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

void parseRadarData(const char *input, RadarInfo *radarInfo) {
    char *input_copy = strdup(input); // Duplicate input to avoid modifying the original
    int planet_index = 0;
    int ship_index = 0;
    char *token;

    // Tokenize the input string by commas
    token = strtok(input_copy, ",");
    while (token != NULL) {
        char type = token[0]; // First character indicates the type
        int values[5];

        if (type == 'P' && planet_index < MAX_PLANETS) {
            // Parse planet data (format: "P id x y collected_by at_base")
            parse_numbers(token + 2, values, 5); // Skip "P "
            radarInfo->planets[planet_index].planet_id = values[0];
            radarInfo->planets[planet_index].x = values[1];
            radarInfo->planets[planet_index].y = values[2];
            radarInfo->planets[planet_index].collected_by = values[3];
            radarInfo->planets[planet_index].at_base = values[4];
            planet_index++;
        } else if (type == 'S' && ship_index < MAX_SHIPS) {
            // Parse ship data (format: "S team ship_id x y broken")
            parse_numbers(token + 2, values, 5); // Skip "S "
            radarInfo->ships[ship_index].team = values[0];
            radarInfo->ships[ship_index].ship_id = values[1];
            radarInfo->ships[ship_index].x = values[2];
            radarInfo->ships[ship_index].y = values[3];
            radarInfo->ships[ship_index].broken = values[4];
            ship_index++;
        } else if (type == 'B') {
            // Parse base station data (format: "B x y")
            parse_numbers(token + 2, values, 2); // Skip "B "
            radarInfo->base.x = values[0];
            radarInfo->base.y = values[1];
        }

        token = strtok(NULL, ","); // Get the next token
    }

    radarInfo->planet_count = planet_index;
    radarInfo->ship_count = ship_index;

    free(input_copy); // Free the duplicated string
}

int calculate_angle(int x1, int y1, int x2, int y2) {
    double angle_rad = atan2(y2 - y1, x2 - x1);
    int angle_deg = (int)(angle_rad * 180 / M_PI);
    if (angle_deg < 0)
        angle_deg += 360;
    return angle_deg;
}

