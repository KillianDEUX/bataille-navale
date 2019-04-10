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


void modif_type(bateau_t *, type_t);/*modifie le type du bateau selon le type donn� */

int fin_bateau_vertical(bateau_t *);/*renvoie la coordonn�e de fin du bateau, ici le y car le bateau est plac� � la vertical*/

int fin_bateau_horizontal(bateau_t *);/*renvoie la coordonn�e de fin du bateau, ici le x car le bateau est plac� � l'horizontal*/

int verif_placement_bateau(bateau_t * ,dir_t, coord_t, coord_t *);/*v�rifie si le bateau peut �tre place aux premi�res coordonn�es selon le tableau de case_t et retourne 0 si impossible, 1 sinon */

void modif_coord(bateau_t * , coord_t );/*modifie les coordonn�es du bateau*/

void modif_direction(bateau_t * , dir_t );/*modifie la direction du bateau*/

void modif_etat(bateau_t * , etat_t );/*modifie l'�tat du bateau*/

void incrementer_nbtouche(bateau_t * );/*incr�mente le nombre de fois que le bateau a �t� touch�*/

void nouveau_bateau(int , bateau_t * );/*cr�� les param�tres de base d'un nouveau bateau*/

int bat_coul(bateau_t );/* v�rifie si le bateau est coul�*/

int toucheunbateau(matrice_case_t, coord_t, bateau_t *);/* renvoie 2 si le bateau est coul�, 1 s il est touch� et 0 si le tir est dans l'eau*/


#endif
