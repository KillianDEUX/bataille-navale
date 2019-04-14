#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "listebateau.h"
#include "matrice.h"

#define DEFAULT_DIRECTION VERTICAL

// L'IA place tous ses bateaux
int placer_bateau_ia(t_liste joueur, matrice_case_t mat, t_liste ia){
	srand(time(NULL));
	int direc;
	coord_t emp;
	dir_t direction;
	t_liste ia_nonplace;
	init_liste(&ia_nonplace);
	bateau_t nouv;
	appliquer_bateau(joueur, ia_nonplace); //copie la liste du joueur dans la liste de l'ia
	en_tete(&ia_nonplace);
	while(!hors_liste(&ia_nonplace)){ //parcours des bateaux de la liste
		do{
			if(!hors_liste(&ia_nonplace)){
				valeur_elt(&ia_nonplace,&nouv);
				direc=rand()%2+1;	// choix aleatoire de la direction
				if(nouv.taille !=1){
					if(direc==1){ //si la valeur aléatoire est 1
						direction=VERTICAL; //la direction est verticale
						do{
							emp.y= rand()%mat.nbc; // choix des coordonnées aleatoires
							emp.x= rand()%mat.nbl;
						}while(emp.x+(nouv.taille)-1 >= mat.nbl); //Verification
					}else{ //si la valeur aléatoire est 2
						direction=HORIZONTAL;//la direction est horizontale
						do{
							emp.y= rand()%mat.nbc; // choix des coordonnées aleatoires
							emp.x= rand()%mat.nbl;
						}while(emp.y+(nouv.taille)-1 >= mat.nbc);//Verification
					}
				}else{
					direction= DEFAULT_DIRECTION; //direction par défaut d'un bateau de taille 1
					emp.y= rand()%mat.nbc; // choix des coordonnées aleatoires
					emp.x= rand()%mat.nbl;
				}
			}
			//printf("direction : %i \n", direc);
			//printf("coord : %i %i \n", emp.x, emp.y);
		}while(!placement_bateau(ia, &nouv, direction, emp, mat)); // ajout du bateau dans la liste si le bateau peut être placé
		suivant(&ia_nonplace); //on passe au bateau suivant
	}
	return 1;
}
