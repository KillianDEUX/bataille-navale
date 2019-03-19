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

// Creer une matrice de taille nbl sur nbc et lui alloue de la mémoire 
matrice_t creer_matrice_adv (int, int);

// Libère la mémoire de la matrice
void detruire_matrice_adv( matrice_t );

// initialise la matrice avec "AUCUNE" couleur;
int init_matrice_adv( matrice_t);

 /* Vérifie si les coordonnées passées en paramètres sont dans la grille*/
int danslagrille(matrice_t, coord_t);

// Ajoute des pions Blancs autour d'un bateau coulé
void eauautourcoule( coord_t, matrice_t);

// Ajoute un pion à la gille suivant le tir
int ajout_pion_matrice( coord_t, matrice_t, t_liste);

// Remet tout les pions à "AUCUN"
int vider_matrice(matrice_t);

// Voir avec la SDL. Ici affichage version terminal
void afficher_matrice_pion( matrice_t);

#endif
