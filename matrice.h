#ifndef __MATRICE_H__
#define __MATRICE_H__

#include "commun.h"

typedef enum etat_case_s{ CASEVIDE, CASETOUCHEE, BATEAUVIDE, BATEAUTOUCHE, BATEAUCOULE }etat_case_t;

typedef struct joueur_case_s{
	coord_t coord;
	etat_case_t etat;
}joueur_case_t ;

typedef struct matrice_case_s {
	int nbl, nbc;
	joueur_case_t **grille;
}matrice_case_t;


matrice_case_t creer_matrice_joueur(int ,int );

void detruire_matrice_joueur(matrice_case_t );

int init_matrice_joueur(matrice_case_t );

void update_case_mat(matrice_case_t, coord_t, etat_case_t );

int danslagrille_joueur(matrice_case_t, coord_t );
#endif
