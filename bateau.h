#ifndef __BATEAU_H__
#define __BATEAU_H__

#include "commun.h"
#include "matrice.h"


typedef enum type_bat {NONE, MINE ,TORPILLEUR, SOUSMARIN,  CROISEUR, PORTEAVION}type_t;
typedef enum dir_bat {AUCUN, VERTICAL, HORIZONTAL}dir_t;
typedef enum etat_bat {FLOTTE, COULE}etat_t;

typedef struct bateau {
	type_t type;
	coord_t coord;
	int taille;
	dir_t dir;
	etat_t etat;
	int nb_touche;
}bateau_t;


void modif_type(bateau_t *, type_t);/*modifie le type du bateau selon le type donné */

int fin_bateau_vertical(bateau_t *);/*renvoie la coordonnée de fin du bateau, ici le y car le bateau est placé à  la vertical*/

int fin_bateau_horizontal(bateau_t *);/*renvoie la coordonnée de fin du bateau, ici le x car le bateau est placé à  l'horizontal*/

void afficher_bateau(bateau_t , int , int );/* permet d'afficher le bateau fourni en paramètre*/

int verif_placement_bateau(bateau_t * , coord_t, coord_t *);/*vérifie si le bateau peut être place aux premières coordonnées selon le tableau de case_t et retourne 0 si impossible, 1 sinon */

void modif_coord(bateau_t * , coord_t );/*modifie les coordonnées du bateau*/

void modif_direction(bateau_t * , dir_t );/*modifie la direction du bateau*/

void modif_etat(bateau_t * , etat_t );/*modifie l'état du bateau*/

void incrementer_nbtouche(bateau_t * );/*incrémente le nombre de fois que le bateau a été touché*/

void nouveau_bateau(int , bateau_t * );/*créé les paramètres de base d'un nouveau bateau*/

int bat_coul(bateau_t );/* vérifie si le bateau est coulé*/

int toucheunbateau(matrice_case_t, coord_t, bateau_t *);/* renvoie 2 si le bateau est coulé, 1 s il est touché et 0 si le tir est dans l'eau*/


#endif
