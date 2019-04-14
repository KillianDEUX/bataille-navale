
#include <stdio.h>
#include <stdlib.h>
#include "bateau.h"
#include "matrice.h"
#include "matricepion.h"


/*renvoie la coordonn�e de fin du bateau, ici le y car le bateau est plac� �la vertical*/
int fin_bateau_vertical(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille-1);
}

/*renvoie la coordonn�e de fin du bateau, ici le x car le bateau est plac� � l'horizontal*/
int fin_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.y + bateau->taille-1);
}


/*verifie si le bateau peut �tre plac� au premi�re coordonn�e selon le tableau de case_t et retourne 0 si impossible */
int verif_placement_bateau(bateau_t * bat,dir_t dir, coord_t emp, coord_t *casesprises){
	int i, j;			
	if(dir == VERTICAL){ //si le bateau est plac� � la verticale
		for(i=emp.x; i <= (bat->taille + emp.x)-1; i++){ //parcours le bateau
			for(j=0; casesprises[j].y != -1; j++){ //parcoursle tableau de coord_t
				if(casesprises[j].x == i && casesprises[j].y == emp.y){ //si les coord actuelles du bateau correspond � la case actuelle du tableau
					//fprintf(stderr, "Erreur : le bateau ne peut pas �tre plac� ici");
					return 0;
				}
			}
		}
	}
	else if(dir == HORIZONTAL){//si le bateau est plac� � l'horizontale
		for(i=emp.y; i <= (bat->taille + emp.x)-1; i++){//parcours le bateau
			for(j=0; casesprises[j].x != -1; j++){//parcoursle tableau de coord_t
				if(casesprises[j].y == i && casesprises[j].x == emp.x){//si les coord actuelles du bateau correspond � la case actuelle du tableau
					//fprintf(stderr, "Erreur : le bateau ne peut pas �tre plac� ici");
					return 0;
				}
			}
		}
	}
	else{
		fprintf(stderr, "erreur direction");
	}
	return 1;
}

/*modifie les coordonn�es du bateau*/
void modif_coord(bateau_t * bat, coord_t emp){
	bat->coord.x = emp.x;
	bat->coord.y = emp.y;
}

/*modifie la direction du bateau*/
void modif_direction(bateau_t * bat, dir_t dir){
	bat->dir = dir;
}
	
/*modifie l'�tat du bateau*/
void modif_etat(bateau_t * bat, etat_t etat){
	bat->etat = etat;
}

void modif_type(bateau_t * bat, type_t type){
		bat->type = type;
}
/*incr�mente le nombre de fois que le bateau a �t� touch�*/
void incrementer_nbtouche(bateau_t * bat){
	bat->nb_touche++;
}

/*cr�� les param�tres de base d'un nouveau bateau*/
void nouveau_bateau(int t, bateau_t * nouveau){
	nouveau->taille = t;
	nouveau->coord.x = -1;
	nouveau->coord.y = -1;
	nouveau->dir = AUCUN;
	nouveau->type = NONE;
	nouveau->etat = FLOTTE;
	nouveau->nb_touche = 0;
}


// verifie si le bateau est coul�
int bat_coul(bateau_t bateau){
	if( bateau.etat == COULE){ //si le bateau est coul�
		return 1;
	}
	return 0;
}

