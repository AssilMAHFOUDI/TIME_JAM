#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H


// #include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define constants for maximum capacities

#define MAX_PLANETS 20
#define MAX_SPACESHIPS 20
#define MAX_FIELD_SIZE 16
#define MAX_TOKEN_SIZE 20

// Structure pour représenter une planète
typedef struct {
    char type;
    int planet_id;
    int abscissa;
    int ordinate;
    int ship_id;
    int saved;
} Planet;

// Structure pour un vaisseau
typedef struct {
    char type; // 'S'
    int team;
    int ship_id;
    int abscissa;
    int ordinate;
    int broken;
} Ship;

// Structure pour la base
typedef struct {
    char type; // 'B'
    int abscissa;
    int ordinate;
} Base;

typedef struct {
    Planet planets[MAX_PLANETS];
    int planet_count;
    Ship ships[MAX_SPACESHIPS];
    int ship_count ;
    Base base;
    int radar_id; // ID du radar
} Radar;

// // Define structures
// typedef struct {
//     int planet_id;
//     int x, y;
//     int ship_id;
//     int saved; // 0 or 1
// } Planet;



// typedef struct {
//     Planet planets[MAX_PLANETS];
//     int planet_count;
//     Spaceship spaceships[MAX_SPACESHIPS];
//     int spaceship_count;
//     BaseStation base_station;
// } RadarData;
// int parse_radar_data(char* radar_string, RadarData* result);
int calculate_angle(int x1, int y1, int x2, int y2); 

 
/**
 * Génère une commande MOVE.
 * @param buffer Buffer où écrire la commande.
 * @param number_sheep Identifiant du vaisseau (1-9).
 * @param angle Angle (0-359).
 * @param speed Vitesse (0-max).
 * @return 0 si OK, >0 code erreur.
 */
int move(char *buffer, int number_sheep, int angle, int speed);
 
/**
 * Génère une commande FIRE (attaquant uniquement).
 * @param buffer Buffer où écrire la commande.
 * @param ship_id Identifiant du vaisseau (1-5).
 * @param angle Angle (0-359).
 * @return 0 si OK, >0 code erreur.
 */
int fire(char *buffer, int ship_id, int angle);
 
/**
 * Génère une commande RADAR (explorateur uniquement).
 * @param buffer Buffer où écrire la commande.
 * @param ship_id Identifiant du vaisseau (6-7).
 * @return 0 si OK, >0 code erreur.
 */
int radar(char *buffer, int ship_id);

void int_to_string(char *dest, int num);
void string_concat(char *dest, const char *str1, int num1, const char *str2, int num2, const char *str3, int num3, const char *end);
int string_to_int(const char *str);
void parse_numbers(const char *token, int *values, int max_values);
void parse_radar_data(Radar *radar_instance, const char *buffer);



 
#endif
 