#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int etat_tir( int taille, case_t cell){
	bateau_t * actuel;
	
	if(toucheunbateau(taille, cell, actuel)){
		actuel->nb_touche++;
		if(actuel->nb_touche == actuel->taille){
			actuel->etat = coule;
			return 2;
		}else{
			return 1;
		}
	}else{
		return 0;
	}
	return -1;
}

int toucheunbateau( int taille, case_t cell, bateau_t * actuel){
	bateau_t * actueltemp= actuel;
	while(!hors_liste()){
		valeur_elt(*actueltemp);
		if(actueltemp->dir=vertical){
			for(int i=0; i<taille; i++){
				if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					return 1;
				}
				actueltemp->coord->y++;
			}
		}else{
			for(int i=0; i<taille; i++){
				if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					return 1;
				}
				actueltemp->coord->x++;
			}
		}
		suivant();
	}
	return 0;
}
