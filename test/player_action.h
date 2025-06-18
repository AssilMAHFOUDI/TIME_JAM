#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H
 
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
 
#endif
 