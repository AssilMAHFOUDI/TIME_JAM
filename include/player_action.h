#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H


// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PLANETS 100
#define MAX_SHIPS 100

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int planet_id;
    int x;
    int y;
    int collected_by;
    int at_base;
} Planet;

typedef struct {
    int team;
    int ship_id;
    int x;
    int y;
    int broken;
} Ship;

typedef struct {
    int planet_count;
    int ship_count;
    Point base;
    Planet planets[MAX_PLANETS];
    Ship ships[MAX_SHIPS];
} RadarInfo;


void parseRadarData(const char *input,  RadarInfo *radarInfo);

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



 
#endif
 