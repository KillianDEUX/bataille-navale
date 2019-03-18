#ifndef __MATRICEPION_H__
#define __MATRICEPION_H__

#include "commun.h"

typedef enum couleur { AUCUNE, BLANC, ROUGE } couleur_t;

typedef struct case_s {
	coord_t coord;
	couleur_t c;
}case_t;

typedef struct matrice_s {
	int nbl, nbc;
	case_t **grille;
}matrice_t;


#include "liste.h"


matrice_t creer_matrice_adv (int, int);
void detruire_matrice_adv( matrice_t );
int init_matrice_adv( matrice_t);
int danslagrille(matrice_t, coord_t); /* vérifie si les */
void eauautourcoule( coord_t, matrice_t);
int ajout_pion_matrice( coord_t, matrice_t, t_liste);
int vider_matrice(matrice_t);
void afficher_matrice_pion( matrice_t);

#endif
