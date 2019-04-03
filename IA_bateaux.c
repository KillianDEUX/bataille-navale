#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "listebateau.h"
#include "matrice.h"

// L'IA place tous ses bateaux
int placer_bateau_ia(t_liste joueur, matrice_case_t mat, t_liste ia){
	srand(time(NULL));
	int direc;
	coord_t emp;
	dir_t direction;
	bateau_t nouv;
	init_liste(&ia);
	appliquer_bateau(joueur, ia);
	printf("Affichage des bateaux de l'IA : Recopie de celui du joueur ( à supprimer évidemment )\n");
	affichage_flotte(ia, mat);
	fprintf(stderr,"DEBUG : Avant le changement de position des bateaux de l'IA \n REMARQUE : Seul le premier bateau à été recopier\n REMARQUE 2 : Les bateaux ne peuvent pas etre les uns à coté des autres mais peuvent se croiser !\n");
	fprintf(stderr," REMARQUE 3 : Dans 'placement_bateau' ajoute un bateau au lieu seulement de remplacer les nouvelles valeurs car la liste de bateau est déjà existante car copiée du joueur 1 ( Faut il créer une fonction différente pour ici ?)\n ");
	en_tete(&ia);
	while(!hors_liste(&ia)){
		do{
			if(!hors_liste(&ia)){
				valeur_elt(&ia,&nouv);
				direc=rand()%2+1;	// choix aleatoire de la direction
				if(direc==1){
					direction=VERTICAL;
				}else{
					direction=HORIZONTAL;
				}
				emp.y= rand()%mat.nbc+1; // choix des coordonnées aleatoires
				emp.x= rand()%mat.nbl+1;
			}
		}while(placement_bateau(ia, &nouv, direction, emp, mat)); // ajout du bateau dans la liste si le bateau peut être placé

		suivant(&ia);
	}
	return 1;
}
