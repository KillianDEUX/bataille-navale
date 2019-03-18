
// En fonction de la case choisis, renvoie une valeur suivant si le tir touche, coule ou rate
int etat_tir( int taille, case_t cell, t_liste joueur){
		return veriftouche(taille, cell, joueur);
}
// pour chaque bateau, verifie son l'état du tir
int veriftouche( int taille, case_t cell, t_liste joueur){
	int touche;
	bateau_t * actueltemp;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,actueltemp);
		touche=toucheunbateau( taille, cell, actueltemp);
		if(touche!=0){
			return touche;
		}
		suivant(&joueur);
	}
	return touche;
}

	// renvoie 2 si coulé, 1 si touché et 0 si dans l'eau
int toucheunbateau( int taille, case_t cell, bateau_t actueltemp){
		if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					actueltemp->nb_touche++;
					if(actueltemp->nb_touche == actueltemp->taille){
						actueltemp->etat = coule;
						return 2;
					}
					return 1;
				}
		return 0;
}

// verifie si le bateau est coulé
int bat_coul(bateau_t bateau, int nb_bat){
	if( bateau->etat=coule){
		return 1;
	}
	return 0;
}

// vérifie si toute la flotte est coulée
int bateaux_coules( t_liste joueur, int nb_bat){
	bateau_t * bateau;
	int c_bat_coul=0;
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,bateau);
		c_bat_coul+=bat_coul(bateau, nb_bat);
		suivant(&joueur);
	}
	if(c_bat_coul==nb_bat){
		return 1;
	}
	return 0;
}
