#ifndef __IAPION_H__
#define __IAPION_H__

// transforme un numéro de case en coordonnées x,y
case_t case_tabtocoord(matrice_pion_t, int);

// transforme des coordonnées x,y en numéro de case 
int case_coordtotab(matrice_pion_t, coord_t);

// Verifie si l'IA peut placer un pion à l'endoit cellule
int autorisation_case(matrice_pion_t, int, coord_t);

// Place un pion de manière pseudo aleatoire
case_t pseudo_aleatoire(matrice_pion_t, int);

// Verifie si l'IA peut placer un pion à l'endoit cellule
int pseudo_aleatoire_autorisation(matrice_pion_t, int);

// Place un pion de manière completement aleatoire
case_t aleatoire(matrice_pion_t);

// Choisis une case éloignés de toutes les autres
case_t est_autour(matrice_pion_t);

/* vérifie si un bateau est touché quelque part, et essaye de viser une case qui est à coté */
int detection_touche (matrice_pion_t);

// Choisis une case de la façon la plus adapté
case_t choisir_case(matrice_pion_t, t_liste);

#endif
