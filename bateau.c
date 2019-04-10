
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
	if(dir == VERTICAL){
		for(i=emp.x; i <= (bat->taille + emp.x)-1; i++){
			for(j=0; casesprises[j].y != -1; j++){
				if(casesprises[j].x == i && casesprises[j].y == emp.y){
					//fprintf(stderr, "Erreur : le bateau ne peut pas �tre plac� ici");
					return 0;
				}
			}
		}
	}
	else if(dir == HORIZONTAL){
		for(i=emp.y; i <= (bat->taille + emp.x)-1; i++){
			for(j=0; casesprises[j].x != -1; j++){
				if(casesprises[j].y == i && casesprises[j].x == emp.x){
					//fprintf(stderr, "Erreur : le bateau ne peut pas �tre plac� ici");
					return 0;
				}
			}
		}
	}
	else{
		fprintf(stderr, "erreur direciton");
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
	if( bateau.etat==COULE){
		return 1;
	}
	return 0;
}





/* renvoie 2 si le bateau est coul�, 1 s'il est touch� et 0 si le tir est dans l'eau*/
int toucheunbateau(matrice_case_t mat, coord_t cell, bateau_t *actueltemp){
		int fin_bat;
		int i,j;
		if(actueltemp->dir == VERTICAL){
			fin_bat = fin_bateau_vertical(actueltemp);
			for(i = actueltemp->coord.x, j = actueltemp->coord.y; j!=fin_bat; j++){
				if (cell.x== i && cell.y == j){
					incrementer_nbtouche(actueltemp);
					if(actueltemp->nb_touche == actueltemp->taille){
						modif_etat(actueltemp, COULE);
						update_case_mat(mat, cell, BATEAUCOULE);
						return 2;
					}
					update_case_mat(mat, cell, BATEAUTOUCHE);
					return 1;
				}
			}
		}
		else if(actueltemp->dir == HORIZONTAL){
			fin_bat = fin_bateau_horizontal(actueltemp);
			for(i = actueltemp->coord.x, j = actueltemp->coord.y; i!= fin_bat; i++){
				if (cell.x== i && cell.y == j){
						incrementer_nbtouche(actueltemp);
						if(actueltemp->nb_touche == actueltemp->taille){
							modif_etat(actueltemp, COULE);
							update_case_mat(mat, cell, BATEAUCOULE);
							return 2;
						}
						else
							update_case_mat(mat, cell, BATEAUTOUCHE);
								
						return 1;
					}
			}
		}
		else
			printf("Direction incorrecte\n");
		update_case_mat(mat, cell, CASETOUCHEE);
		return 0;
}
