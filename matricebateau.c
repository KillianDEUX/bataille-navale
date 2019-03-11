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


void type_bateau(t_liste joueur){
	en_tete(&joueur);
	bateau_t *actuel;
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, *actuel);
		if(joueur->actuel->taille == 1){
			joueur->actuel->type = mine;
		}
		if(joueur->actuel->taille == 2){
			joueur->actuel->type = torpilleur;
		}
		if(joueur->actuel->taille == 3){
			joueur->actuel->type = sousmarin;
		}
		if(joueur->actuel->taille == 4){
			joueur->actuel->type = croiseur;
		}
		if(joueur->actuel->taille == 5){
			joueur->actuel->type = porteavion;
		}
		suivant(&joueur);
	}
		
}


void choixbateau(t_liste joueur, int taille){
       init_liste(&joueur);
       int nbbat=0;
       int t;
       bateau_t nouveau;
       int nbmaxbat = (0,06 * (taille*taille)) - (0,3 * taille) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bâteau voulez-vous avoir ?(différent de 0 et inférieur à : %i) : ", nbmaxbat);
              scanf("%i", &nbbat);
       }
       
       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     en_tete(&joueur);
                     joueur->nouveau.taille = t;
                     joueur->nouveau.coord.x = -1;
                     joueur->nouveau.coord.y = -1;
                     joueur->nouveau.dir = aucun;
                     joueur->nouveau.type = aucun;
                     joueur->nouveau.etat = flotte;
                     joueur->nouveau.nb_touche = 0;
                     ajout_droit(&joueur, nouveau);
              }
       }
}

void appliquer_bateau(t_liste joueur1, t_liste joueur2){
		en_tete(&joueur1);
		en_tete(&joueur2);
		bateau_t nouveau;
		while(!hors_liste(&joueur1)){
			valeur_elt(&joueur1, *nouveau);
			ajout_droit(&joueur2, *nouveau);
			suivant(&joueur1);
			suivant(&joueur2);
		}
}
int fin_bateau_vertical(t_liste* joueur, bateau_t *bateau){
	return (joueur->bateau->coord.y + joueur->bateau->taille);
}
       
int fin_bateau_horizontal(t_liste* joueur, bateau_t *bateau){
	return (joueur->bateau->coord.x + joueur->bateau->taille); 
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_bateau((t_liste joueur, int taille){
	bateau_t * actuel;
	for(int i=0; i<taille ; i++){
       		for(int j=0; j<taille ; j++){
       			en_tete(&joueur);
       			while(!hors_liste(&joueur)){
       				valeur_elt(&joueur, *actuel);
       				if(i==actuel->coord.x && j==actuel->coord.y){
	       				if(actuel->dir == vertical){
	       					for(int k=j; k< (fin_bateau_vertical(&joueur, actuel)); k++){
	       						printf("[.]");
	       					}
	       				}
	       				if(actuel->dir == horizontal){
	       					for(int k=j; k< (fin_bateau_horizontal(&joueur, actuel)); k++){
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
void cases_prises(t_liste joueur, case_t* case_nonlibres, int taille){
	bateau_t *bat;	
	int fin_bat;
	int i, compteur;
	case_t actuel;
	en_tete();  
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, *bat);
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


int placement_bateau(t_liste joueur, bateau_t * bat, dir_t dir, case_t emp, int taille_mat){
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
	    joueur->bat->coord.x = emp.x;
	    joueur-> bat->coord.y = emp.y;
	    joueur->bat->dir = dir;
	    joueur-> bat->etat = flotte;
	    joueur->bat->nb_touche = 0;
	    en_tete(&joueur);
	    while(!hors_liste(&joueur));
	    precedent(&joueur);
	    ajout_droit(&joueur, bat);
	}
	free(casesprises);    
    return result;
}

	
void placer_bateau(t_liste joueur, int taille_mat){
	type_t nom_bat;
	int dir_donne;
	int type_donne;
	dir_t direction;
	case_t emp;
	bateau_t * nouv;
	printf("Quel est le nom du bateau que vous voulez placer ?(donner un entier selon : mine=1 ,torpilleur=2, sousmarin=3,  croiseur=4 ou porteavion=5)");
	scanf("%i", &type_donne);
	if(type_donne <= 5 && type_donne >= 1){
		joueur->nouv->type = type_donne;
	}
	en_tete(&joueur);
	valeur_elt(&joueur, *nouv);
	while(!hors_liste(&joueur) || nouv->type == nom_bat){
		valeur_elt(&joueur, *nouv);
		suivant(&joueur);
	}
	if(!hors_liste(&joueur)){
		printf("Dans quelle direction voulez-vous placer le bateau ?(donner un entier selon : vertical = 1, horizontal = 2)");
		scanf("%i", &dir_donne);
		if(dir_donne <= 2 && dir_donne >= 1){
			direction = dir_donne;
		}
		do{
			printf("Quelles sont les coordonnées a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", taille_mat);
			scanf("%i", &emp.x);
		}while(emp.x <1 || emp.x > taille_mat);
		
		do{
			printf("\n y = ");
			scanf("%i", &emp.y);
		}while(emp.y < 1 || emp.y > taille_mat);
		if(placement_bateau(joueur, nouv, direction, emp, taille_mat)){
			printf("Le bateau a été placé");
			free(nouv);
			return 1;
		}
		else{
			printf("Le bateau n'a pas pu être placé");
			return 0;
		}
	}
}
