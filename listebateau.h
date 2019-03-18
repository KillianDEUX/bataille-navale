#ifndef __LISTEBATEAU_H__
#define __LISTEBATEAU_H__


#include "matricepion.h"
#include "liste.h"
#include "bateau.h"

void type_bateau(t_liste);
void choixbateau(t_liste,int);
void appliquer_bateau(t_liste,t_liste);
int fin_bateau_vertical(t_liste *, bateau_t *);
int fin_bateau_horizontal(t_liste *, bateau_t *);
void afficher_matrice_bateau(t_liste, int);
void cases_prises(t_liste, case_t *, int);
int placement_bateau(t_liste, bateau_t *, dir_t, case_t, int);
void placer_bateau(t_liste, int);
int bateau_plus_petit(t_liste);

#endif
