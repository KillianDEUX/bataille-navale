#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct case_s {
	int x;
	int y;
	couleur_t c;
}case_t;
typedef enum type_bat {none, mine ,torpilleur, sousmarin,  croiseur, porteavion}type_t;
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
			actuel->type = sousmarin;
		}
		if(actuel->taille == 4){
			actuel->type = croiseur;
		}
		if(actuel->taille == 5){
			actuel->type = porteavion;
		}
		suivant();
	}
		
}


void choixbateau(int taille){
       init_liste();
       int nbbat=0;
       int t;
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
       
int fin_bateau_vertical(bateau_t *bateau){
	return (bateau->coord.y + bateau->taille);
}
       
int fin_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille); 
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_bateau(int taille){
	bateau_t * actuel;
	for(int i=0; i<taille ; i++){
       		for(int j=0; j<taille ; j++){
       			en_tete();
       			while(!hors_liste()){
       				valeur_elt(*actuel);
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
	       			suivant();
	       		}
       		}
		printf("\n");
	}
}

/*  */
void cases_prises(case_t* case_nonlibres, int taille){
	bateau_t *bat;	
	int fin_bat;
	int i, compteur;
	case_t actuel;
	en_tete();  
	while(!hors_liste()){
		valeur_elt(*bat);
		if(bat->dir == vertical){
	       		fin_bat = fin_bateau_vertical(bat);
	       		for(i=bat->coord.y,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.y){ 
					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = bat->actuel;
							compteur++;
					}
					actuel.x++;		
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = bat->actuel;
							compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = bat->actuel;
							compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
			}
		}
		if(bat->dir == horizontal){
			fin_bat = fin_bateau_horizontal(bat);
       			for(i=bat->coord.x,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.x){ 
					actuel.y--;
					if(danslagrille(taille, actuel)){	
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = bat->actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = bat->actuel;
						compteur++;
					}
				}
			}			
		}
	}
	case_nonlibres[compteur].x = -1;
	case_nonlibres[compteur].y = -1;
}


int placement_bateau(bateau_t * bat, dir_t dir, case_t emp, int taille_mat){
	int i, j;
	int result= 1;
	case_t *casesprises = malloc(sizeof(case_t)*taille_mat*taille_mat);
	cases_prises(casesprises,taille_mat);
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
    if(result){
	    bat->coord.x = emp.x;
	    bat->coord.y = emp.y;
	    bat->dir = dir;
	    bat->etat = flotte;
	    bat->nb_touche = 0;
	    en_tete();
	    while(!hors_liste());
	    precedent();
	    ajout_droit(bat);
	}
	free(casesprises);    
    return result;
}

	
void placer_bateau(int taille_mat){
	type_t nom_bat;
	int dir_donne;
	int type_donne;
	dir_t direction;
	case_t emp;
	bateau_t * nouv;
	printf("Quel est le nom du bateau que vous voulez placer ?(donner un entier selon : mine=1 ,torpilleur=2, sousmarin=3,  croiseur=4 ou porteavion=5)");
	scanf("%i", &type_donne);
	if(type_donne <= 5 && type_donne >= 1){
		nouv->type = type_donne;
	}
	en_tete();
	valeur_elt(*nouv);
	while(!hors_liste() || nouv->type == nom_bat){
		valeur_elt(*nouv);
		suivant();
	}
	if(!hors_liste()){
		printf("Dans quelle direction voulez-vous placer le bateau ?(donner un entier selon : vertical = 1, horizontal = 2)");
		scanf("%i", &dir_donne);
		if(dir_donne <= 5 && dir_donne >= 1){
			nouv->dir = dir_donne;
		}
		do{
			printf("Quelles sont les coordonnées a laquelle vous voulez placer le bateau ?(entre 1 et %i \n x = ", taille_mat);
			scanf("%i", &emp.x);
		}while(emp.x <1 || emp.x > taille_mat);
		
		do{
			printf("y = ");
			scanf("%i", &emp.y);
		}while(emp.y < 1 || emp.y > taille_mat);
		if(placement_bateau(nouv, direction, emp, taille_mat)){
			printf("Le bateau a été placé");
		}
	}		
}
