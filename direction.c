#include "direction.h"

const int NB_DIRECTION=4;

// Avance de nb_pas case dans la direction dir depuis la case depart
coord_t direction_avancer(direction_t dir, coord_t depart, int nb_pas){
	coord_t arrivee= depart;
	if(dir == NORD)
		arrivee.y += nb_pas;
	if(dir == SUD)
		arrivee.y -= nb_pas;
	if(dir == EST)
		arrivee.x += nb_pas;
	if(dir == OUEST)
		arrivee.x -= nb_pas;
	return arrivee;
}

// Passe à la direction suivnte N->E->S->O->N
direction_t direction_suivante(direction_t dir){
	return (dir+1)%NB_DIRECTION;
}

// Retourne La direction initiale qui est NORD
direction_t direction_debut(){
	return NORD;
}

// Renvoie la chaine de caractère correspondant à la direction
char* direction_str(direction_t dir){
	if(dir==NORD) return "NORD";
	if(dir==SUD) return "SUD";
	if(dir==EST) return "EST";
	if(dir==OUEST) return "OUEST";
	return "ERREUR";
}
