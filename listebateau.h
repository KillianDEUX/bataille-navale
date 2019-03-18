#ifndef __LISTEBATEAU_H__
#define __LISTEBATEAU_H__


#include "matricepion.h"
#include "liste.h"
#include "bateau.h"

int etat_tir( int taille, case_t cell, t_liste joueur);
int veriftouche( int taille, case_t cell, t_liste joueur);
int bateaux_coules( t_liste joueur, int nb_bat);
void type_bateau(t_liste);
void appliquer_bateau(t_liste,t_liste);
void affichage_flotte(t_liste joueur, int taille)
void cases_prises(t_liste, case_t *, int);
int placement_bateau(t_liste, bateau_t *, dir_t, case_t, int);
void placer_bateau(t_liste, int);
void choixbateau(t_liste,int);
int bateau_plus_petit(t_liste);

#endif
