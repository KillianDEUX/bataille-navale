
#include <stdio.h>
#include <stdlib.h>
#include "bateau.h"

/*modifie le type du bateau selon sa taille */
void modif_type_bat(bateau_t * actuel){
	if(actuel->taille == 1){
		actuel->type = MINE;
	}
	if(actuel->taille == 2){
		actuel->type = TORPILLEUR;
	}
	if(actuel->taille == 3){
		actuel->type = SOUSMARIN;
	}
	if(actuel->taille == 4){
		actuel->type = CROISEUR;
	}
	if(actuel->taille == 5){
		actuel->type = PORTEAVION;
	}
}

/*renvoie la coordonnée de fin du bateau, ici le y car le bateau est placé à la vertical*/
int fin_bateau_vertical(bateau_t *bateau){
	return (bateau->coord.y + bateau->taille);
}

/*renvoie la coordonnée de fin du bateau, ici le x car le bateau est placé à l'horizontal*/
int fin_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille);
}

/* permet d'afficher le bateau fourni en paramètre*/
void afficher_bateau(bateau_t actuel, int i, int j){
		if(i==actuel->coord.x && j==actuel->coord.y){
	       	if(actuel->dir == vertical){
	       		for(int k=j; k< (fin_bateau_vertical(actuel)); k++){
	       			printf("[.]");
	       		}
	       	}
	       	if(actuel->dir == horizontal){
	       		for(int k=j; k< (fin_bateau_horizontal(actuel)); k++){
	       			printf("[.]");
	       		}
	       	}
	    }
	    else{
	       	printf("[ ]");
	    }
}

/*verifie si le bateau peut être placé au première coordonnée selon le tableau de case_t et retourne 0 si impossible */
void verif_placement_bateau(bateau_t * bat, coord_t emp, coord_t *casesprises, int * result){
		int i, j;
		if(dir == vertical){
			for(i=emp.y; i<(bat->taille+emp.y) && result; i++){
				for(j=0; casesprises[j].y != -1 && result; j++){
					if(casesprises[j].y == i && casesprises[j].x == emp.x){
						printf("Erreur : le bateau ne peut pas être placé ici");
						result = 0;
					}
				}
			}
		}
		else {//if(dir == horizontal){
			for(i=emp.x; i<(bat->taille+emp.x) && result; i++){
				for(j=0; casesprises[j].x != -1 && result; j++){
					if(casesprises[j].x == i && casesprises[j].y == emp.y){
						printf("Erreur : le bateau ne peut pas être placé ici");
						result = 0;
					}
				}
			}
		}
}

/*modifie les coordonnées du bateau*/
void modif_coord(bateau_t * bat, coord_t emp){
	bat->coord.x = emp.x;
	bat->coord.y = emp.y;
}

/*modifie la direction du bateau*/
void modif_direction(bateau * bat, dir_t dir){
	bat->dir = dir;
}
	
/*modifie l'état du bateau*/
void modif_etat(bateau_t * bat, etat_t etat){
	bat->etat = etat;
}

/*incrémente le nombre de fois que le bateau a été touché*/
void incrementer_nbtouche(bateau_t * bat){
	actueltemp->nb_touche++;
}

/*créé les paramètres de base d'un nouveau bateau*/
void nouveau_bateau(int t, bateau_t nouveau){
	nouveau.taille = t;
	nouveau.coord.x = -1;
	nouveau.coord.y = -1;
	nouveau.dir = ANCUN;
	nouveau.type = NONE;
	nouveau.etat = FLOTTE;
	nouveau.nb_touche = 0;
}


// verifie si le bateau est coulé
int bat_coul(bateau_t bateau){
	if( bateau->etat==COULE){
		return 1;
	}
	return 0;
}



/* renvoie 2 si le bateau est coulé, 1 s'il est touché et 0 si le tir est dans l'eau*/ /*A CHANGER CAR NE VERIFIE QUE LA PREMIERE COORDONNEE DU BATEAU*/
int toucheunbateau( coord_t cell, bateau_t *actueltemp){
		if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					incrementer_nbtouche(actueltemp);
					if(actueltemp->nb_touche == actueltemp->taille){
						modif_etat(actueltemp, COULE);
						return 2;
					}
					return 1;
				}
		return 0;
}
