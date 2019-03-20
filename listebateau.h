#ifndef __LISTEBATEAU_H__
#define __LISTEBATEAU_H__


#include "matricepion.h"
#include "liste.h"
#include "bateau.h"

char* typebat_str(type_t); // Transforme un type en chaine de caractère
int etat_tir( matrice_t, coord_t , t_liste );// En fonction de la case choisis, renvoie une valeur suivant si le tir touche, coule ou rate
int veriftouche(coord_t , matrice_t , t_liste );// pour chaque bateau, verifie son l'état du tir
int bateaux_coules( t_liste , int );// vérifie si toute la flotte est coulé
int type_bateau(t_liste);//rempli la t_liste de bateau par leur type selon leur taille
int appliquer_bateau(t_liste,t_liste);//copie la liste de bateau du premier t_liste dans le deuxième t_liste
void affichage_flotte(t_liste, matrice_t);//affiche la flotte d'un joueur
void cases_prises(t_liste, coord_t *, matrice_t);//renvoie un pointeur sur un tableau des cases non disponibles pour poser les bateaux
int placement_bateau(t_liste, bateau_t *, dir_t, coord_t, matrice_t);//applique la direction et les coordonnées du bateau transmis de la t_liste si les cases sont disponibles
void placer_bateau(t_liste, matrice_t);//demande au joueur où il veut placer le nième bateau
void choixbateau(t_liste, matrice_t);//demande au premier jouer le nombre de bateau qu'il veut et leur taille
int bateau_plus_petit(t_liste);//renvoie la taille du bateau le plus petit de la t_liste

#endif
