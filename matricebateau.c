#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

typedef enum type_bat {aucun, mine ,torpilleur, sous-marin,  croiseur, porte-avion}type_t;
typedef enum dir_bat {aucun, vertical, horizontal}dir_t;
typedef enum etat_bat {flotte, coule}etat_t;

typedef struct bateau {
	type_t type;
	case_t coord;
	int taille;
	dir_t dir;
	etat_t etat;
	int nb_touche;
}bateau_t;


void type_bateau(){
	en_tete();
	bateau_t *actuel;
	while(!hors_liste()){
		valeur_elt(*actuel);
		if(actuel->taille == 1){
			actuel->type = mine;
		}
		if(actuel->taille == 2){
			actuel->type = torpilleur;
		}
		if(actuel->taille == 3){
			actuel->type = sous-marin;
		}
		if(actuel->taille == 4){
			actuel->type = croiseur;
		}
		if(actuel->taille == 5){
			actuel->type = porte-avion;
		}
		suivant();
	}
		
}


void choixbateau(int taille){
       init_liste();
       int nbbat=0;
       bateau_t nouveau;
       int nbmaxbat = (0,06 * (taille*taille)) - (0,3 * taille) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bÃ¢teau voulez-vous avoir ?(diffÃ©rent de 0 et infÃ©rieur Ã  la moitiÃ© du nombre de case du terrain de jeu) : ");
              scanf("%i", &nbbat);
       }
       
       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     en_tete();
                     nouveau.taille = t;
                     nouveau.coord.x = -1;
                     nouveau.coord.y = -1;
                     nouveau.dir = aucun;
                     nouveau.type = aucun;
                     nouveau.etat = flotte;
                     nouveau.nb_touche = 0;
                     ajout_droit(nouveau);
              }
       }
}
       
int position_bateau_vertical(bateau_t *bateau){
	return (bateau->coord.y + bateau->taille);
}
       
int position_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille); 
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_bateau(int taille){
	int coord.x, coord.y;
	bateau_t * actuel;
	for(int i=0; i<taille ; i++){
       	for(int j=0; j<taille ; j++){
       		entete();
       		while(!hors_liste()){
       			valeur_elt(*actuel);
       			if(i==actuel->coord.x && j==actuel->coord.y){
       				if(actuel->dir == vertical){
       					for(int k=j; k< (position_bateau_vertical(*actuel)); k++){
       						printf("[.]");
       					}
       				}
       				if(actuel->dir == horizontal){
       					for(int k=j; k< (position_bateau_horizontal(*actuel)); k++){
       						printf("[.]");
       					}
       				}
       			}
       			else{
       				printf("[]");
       			}
       			suivant();
       		}
       	}
    }
}


case_t * cases_prises(case_t *case_nonlibres[], int taille){
	bateau_t *bat;	
	int fin_bat;
	int i, compteur;
	case_t actuel;
	en_tete();  
	while(!hors_liste()){
		valeur_elt(*bat);
		if(bat->dir == vertical){
       		fin_bat = position_bateau_vertical(bat);
       		for(i=bat->coord.y,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.y){ 
						actuel.x--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
       					actuel.x--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
					else if(i==fin_bat){
						actuel.x--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
       					actuel.x--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
					else{
						*case_nonlibres[compteur]->x =actuel.x ;
						*case_nonlibres[compteur]->y =actuel.y ; 
						actuel.x--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
			}
						
       	}
		if(actuel->dir == horizontal){
			fin_bat = position_bateau_horizontal(bat);
       		for(i=bat->coord.x,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.x){ 
						actuel.y--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
       					actuel.y--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y--;
						if(danslagrille(taille, actuel)){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
					else if(i==fin_bat){
						actuel.y--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.x++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
       					actuel.y--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
					else{
						*case_nonlibres[compteur]->x =actuel.x ;
						*case_nonlibres[compteur]->y =actuel.y ; 
						actuel.y--;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
						actuel.y++;
						if(danslagrille(taille, actuel){
								*case_nonlibres[compteur]->x = bat->actuel.x;
								*case_nonlibres[compteur]->y = bat->actuel.y;
								compteur++;
						}
					}
			}
						
		}
	}
	*case_nonlibres[compteur]->x = -1;
	*case_nonlibres[compteur]->y = -1;
	return case_nonlibres;
}


int placement_bateau(bateau_t bat, dir_t dir, case_t emp, int taille_mat){
	int coord.x, coord.y;
	int i, j;
	case_t *casesprises[];
	casesprises[] = cases_prises(*case_nonlibres[],taille_mat);
	if(dir == verticale){
		for(i=emp->y; i<(bat->taille+emp->y); i++){
			for(j=0; casesprises[j]->y != -1; j++){
				if(casesprises[j]->y == i && casesprises[j]->x == emp->x){
					printf("Erreur : le bateau ne peut pas être placé ici");
					return 0;
				}
			}
		}
    }
    if(dir == horizontal){
		for(i=emp->x; i<(bat->taille+emp->x); i++){
			for(j=0; casesprises[j]->x != -1; j++){
				if(casesprises[j]->x == i && casesprises[j]->y == y){
					printf("Erreur : le bateau ne peut pas être placé ici");
					return 0;
				}
			}
		}
    }
    bat->coord->x = emp->x;
    bat->coord->y = emp->y;
    bat->dir = dir;
    bat->etat = flotte;
    bat->nbtouche = 0;
    en_tete();
    while(!hors_liste());
    precedent();
    ajout_droit(bat);
    return 1;
}

	
void placer_bateau(){
	
}
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
