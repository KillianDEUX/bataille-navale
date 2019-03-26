#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"

// L'IA place tous ses bateaux
int placer_bateau_ia(t_liste joueur, matrice_t mat, t_liste ia){
	srand(time(NULL));
	coord_t emp;
	dir_t direction;
	bateau_t nouv;
	appliquer_bateau(joueur, ia);
	en_tete(&ia);
	while(!hors_liste(&ia)){
		do{
			valeur_elt(&ia,&nouv);
			if(!hors_liste(&ia)){
				direction= rand()%2+1;	// choix aleatoire de la direction
				emp.y= rand()%mat.nbc+1; // choix des coordonnées aleatoires
				emp.x= rand()%mat.nbl+1;
			}
		}while(placement_bateau(ia, nouv, direction, emp, mat)); // ajout du bateau dans la liste si le bateau peut être placé
		suivant(&ia);
	}
	return 1;
}
