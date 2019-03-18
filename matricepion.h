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
void detruire_matrice_adv( case_t **);
int init_matrice_adv(int, case_t**);
int danslagrille(int, case_t); /* vérifie si les */
void eauautourcoule( int, case_t, case_t**);
int ajout_pion_matrice( int, case_t, case_t **, t_liste); // à revoir
int vider_matrice(int, case_t **);
void afficher_matrice_pion( int, case_t **);

#endif
