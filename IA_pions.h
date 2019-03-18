#ifndef __IAPION_H__
#define __IAPION_H__

case_t case_tabtocoord(int, int);
int case_coordtotab(int, case_t);
int autorisation_case(int, int, case_t);
case_t pseudo_aleatoire(int, int);
int pseudo_aleatoire_autorisation(int, int);
case_t aleatoire(int);
case_t est_autour(int ,case_t **);
int detection_touche (int, case_t **);
case_t choisir_case(int, case_t **, t_liste);

#endif
