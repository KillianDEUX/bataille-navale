#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "liste.h"
#include "matricebateau.h"
#include "matricepion.h"

int etat_tir( int taille, case_t cell, t_liste joueur){
	if(toucheunbateau(taille, cell, joueur)==2){
			return 2;
	}else if(toucheunbateau(taille, cell, joueur)==1){{
			return 1;
	}else{
		return 0;
	}
}

int toucheunbateau( int taille, case_t cell, t_liste joueur){
	bateau_t * actueltemp;
	en_tete(&joueur);
	
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,actueltemp);
		if(actueltemp->dir=vertical){
			for(int i=0; i<taille; i++){
				if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					actueltemp->nb_touche++;
					if(actueltemp->nb_touche == actueltemp->taille){
						actueltemp->etat = coule;
						return 2;
					}
					return 1;
				}
				actueltemp->coord->y++;
			}
		}else{
			for(int i=0; i<taille; i++){
				if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					actueltemp->nb_touche++;
					if(actueltemp->nb_touche == actueltemp->taille){
						actueltemp->etat = coule;
						return 2;
					}
					return 1;
				}
				actueltemp->coord->x++;
			}
		}
		suivant(&joueur);
	}
	return 0;
}


int bateaux_coules( t_liste joueur, int nb_bat){
	bateau_t * bateau;
	int c_bat_coul=0;
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,bateau);
		if( bateau->etat=coule){
			c_bat_coul++;
		}
		suivant(&joueur);
	}
	if(c_bat_coul==nb_bat){
		return 1;
	}
	return 0;
}
