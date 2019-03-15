#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "matricebateau.h"
#include "matricepion.h"

int placer_bateau_ia(t_liste joueur, int taille_mat, t_liste ia){
	srand(time(NULL));
	case_t emp;
	dir_t direction;
	bateau_t nouv;
	appliquer_bateau(t_liste joueur, t_liste ia);
	en_tete(&ia);
	while(!hors_liste(&ia)){
		do{
			valeur_elt(&ia,nouv);
			if(!hors_liste(&ia)){
				direction= rand()%2+1;
				emp.y= rand()%taille_mat+1;
				emp.x= rand()%taille_mat+1;
			}
		}while(placement_bateau(ia, nouv, direction, emp, taille_mat));
		suivant(&ia);
	}
	return 1;
}
