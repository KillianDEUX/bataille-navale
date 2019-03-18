#ifndef __IAPION_H__
#define __IAPION_H__

case_t case_tabtocoord(matrice_t, int);
int case_coordtotab(matrice_t, coord_t);
int autorisation_case(matrice_t, int, coord_t);
case_t pseudo_aleatoire(matrice_t, int);
int pseudo_aleatoire_autorisation(matrice_t, int);
case_t aleatoire(matrice_t);
case_t est_autour(matrice_t);
int detection_touche (matrice_t);
case_t choisir_case(matrice_t, t_liste);

#endif
