#ifndef __BATEAU_H__
#define __BATEAU_H__

#include "commun.h"

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


void modif_type_bat(bateau_t actuel);
int fin_bateau_vertical(bateau_t *bateau);
int fin_bateau_horizontal(bateau_t *bateau);
void afficher_bateau(bateau_t actuel, int i, int j);

void verif_placement_bateau(bateau_t * bat, case_t *casesprises, int * result);
void implanter_coordonnee_bateau(bateau_t * bat, case_t emp, dir_t dir);
void implanter_nouveau_bateau(int t, bateau_t nouveau);
int bat_coul(bateau_t bateau);/* */
int toucheunbateau( int taille, case_t cell, bateau_t actueltemp);

#endif
