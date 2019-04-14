#ifndef __MATRICEPION_H__
#define __MATRICEPION_H__

#include "commun.h"
#include "listebateau.h"


typedef enum couleur { AUCUNE, BLANC, ROUGE } couleur_t;

typedef struct case_s {
	coord_t coord;
	couleur_t c;
}case_t;

typedef struct matrice_s {
	int nbl, nbc;
	case_t **grille;
}matrice_pion_t;


#include "liste.h"

// creer la grille en fonction des choix du joueur
matrice_pion_t choixgrille(matrice_pion_t);

// Creer une matrice de taille nbl sur nbc et lui alloue de la mémoire 
matrice_pion_t creer_matrice_adv (int, int);

// Libère la mémoire de la matrice
void detruire_matrice_adv( matrice_pion_t );

// initialise la mastrice avec "AUCUNE" couleur;
int init_matrice_adv( matrice_pion_t);

 /* Vérifie si les coordonnées passées en paramètres sont dans la grille*/
int danslagrille(matrice_pion_t, coord_t);

// Ajoute des pions Blancs autour d'un bateau coulé
void eauautourcoule( coord_t, matrice_pion_t, t_liste);

//Renvoie la bateau auquel la coordonnée transmise appartient
bateau_t recherche_bat(coord_t, t_liste);

// Ajoute un pion à la gille suivant le tir
int ajout_pion_matrice( coord_t, matrice_case_t, matrice_pion_t, t_liste);

// Remet tout les pions à "AUCUN"
int vider_matrice(matrice_pion_t);

// Voir avec la SDL. Ici affichage version terminal
void afficher_matrice_pion( matrice_pion_t);

#endif
