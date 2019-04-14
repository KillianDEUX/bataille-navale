#ifndef __LISTEBATEAU_H__
#define __LISTEBATEAU_H__

#include "commun.h"
#include "liste.h"
#include "bateau.h"
#include "matrice.h"


// Transforme un type en chaine de caract�re
char * typebat_str(type_t); 

//affiche la l�gende de la matrice
void afficher_legende();

// pour chaque bateau, verifie son l'�tat du tir
int veriftouche(coord_t , matrice_case_t , t_liste );

// En fonction de la case choisis, renvoie une valeur suivant si le tir touche, coule ou rate
int etat_tir( matrice_case_t, coord_t , t_liste );

// v�rifie si toute la flotte est coul�
int bateaux_coules( t_liste , int );

//rempli la t_liste de bateau par leur type selon leur taille
int type_bateau(t_liste);

//copie la liste de bateau du premier t_liste dans le deuxi�me t_liste
int appliquer_bateau(t_liste,t_liste);

//affiche la flotte d'un joueur
void affichage_flotte(t_liste, matrice_case_t);

//renvoie un pointeur sur un tableau des cases non disponibles pour poser les bateaux
void parcours_matrice(t_liste, coord_t *, matrice_case_t);

//applique la direction et les coordonn�es du bateau transmis de la t_liste si les cases sont disponibles
int placement_bateau(t_liste, bateau_t *, dir_t, coord_t, matrice_case_t);

//demande au joueur o� il veut placer le ni�me bateau
void placer_bateau(t_liste, t_liste, matrice_case_t);

//demande au premier jouer le nombre de bateau qu'il veut et leur taille
int choixbateau(t_liste, matrice_case_t);

//renvoie la taille du bateau le plus petit de la t_liste
int bateau_plus_petit(t_liste);

int toucheunbateau(matrice_case_t, coord_t, t_liste);/* renvoie 2 si le bateau est coul�, 1 s il est touch� et 0 si le tir est dans l'eau*/

#endif
