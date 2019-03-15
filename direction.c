#include "direction.h"
#include "matricepion.h"


case_t direction_avancer(direction_t dir, case_t depart, int nb_pas, int taille){
	case_t arrivee;
	if(dir == NORD)
		arrivee.y += nb_pas; 
	if(dir == SUD)
		arrivee.y -= nb_pas;
	if(dir == EST)
		arrivee.x += nb_pas; 
	if(dir == OUEST)
		arrivee.x -= nb_pas; 
	if(danslagrille(taille,))
		return arrivee;
}

direction_t direction_suivante(direction_t dir){
	return (dir+1)%NB_DIRECTION;
}

direction_t direction_debut(){
	return NORD;
}

char* direction_str(direction_t dir){
	if(dir==NORD) return "NORD";
	if(dir==SUD) return "SUD";
	if(dir==EST) return "EST";
	if(dir==OUEST) return "OUEST";
}


