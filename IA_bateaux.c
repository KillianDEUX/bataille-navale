#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"

int placer_bateau_ia(t_liste joueur, matrice_t mat, t_liste ia){
	srand(time(NULL));
	coord_t emp;
	dir_t direction;
	bateau_t *nouv;
	appliquer_bateau(joueur, ia);
	en_tete(&ia);
	while(!hors_liste(&ia)){
		do{
			valeur_elt(&ia,nouv);
			if(!hors_liste(&ia)){
				direction= rand()%2+1;
				emp.y= rand()%mat.nbc+1;
				emp.x= rand()%mat.nbl+1;
			}
		}while(placement_bateau(ia, nouv, direction, emp, mat));
		suivant(&ia);
	}
	return 1;
}
