#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include "matricepion.h" //pour coord_t

typedef enum { NORD=0, EST, SUD, OUEST} direction_t;
const int NB_DIRECTION=4;

// Avance de nb_pas case dans la direction dir depuis la case depart
coord_t direction_avancer(direction_t, coord_t, int);

// Passe à la direction suivnte N->E->S->O->N
direction_t direction_suivante(direction_t);

// Retourne La direction initiale qui est NORD
direction_t direction_debut();

// Renvoie la chaine de caractère correspondant à la direction
char* direction_str(direction_t);

#endif
