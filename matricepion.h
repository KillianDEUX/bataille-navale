#ifndef __MATRICEPION_H__
#define __MATRICEPION_H__

typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct case_s {
	int x;
	int y;
	couleur_t c;
}case_t;

#include "liste.h"


case_t **creer_matrice_adv (int);
void detruire_matrice_adv( case_t **);
int init_matrice_adv(int, case_t**);
int danslagrille(int, case_t);
void eauautourcoule( int, case_t, case_t**);
int ajout_pion_matrice( int, case_t, case_t **, t_liste); // à revoir
int vider_matrice(int, case_t **);
void afficher_matrice_pion( int, case_t **);

#endif
