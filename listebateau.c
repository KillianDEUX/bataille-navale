#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"
#include "matrice.h"
#include "bateau.h"
#include "lettre.h"

#define DEFAULT_DIRECTION VERTICAL

// Transforme un type en chaine de caractère
char* typebat_str(type_t type){
	if(type==MINE) return "MINE";
	if(type==TORPILLEUR) return "TORPILLEUR";
	if(type==SOUSMARIN) return "SOUS-MARIN";
	if(type==CROISEUR) return "CROISEUR";
	if(type==PORTEAVION) return "PORTE-AVION";
	return "ERREUR";
}

void afficher_legende(){
	printf(" \n Légende : \n");
	printf("-   : la case ne contient rien \n");
	printf("- o : la case a été touché \n");
	printf("- . : la case contient un bout de bateau non touché \n");
	printf("- * : la case contient un bout de bateau touché \n");
	printf("- ! : la case contient un bout de bateau coulé \n");
	printf("Pour la grille de tir : \n");
	printf("- . : la case n'a pas encore été visé \n");
	printf("- 0 : Le tir est dans l'eau \n");
	printf("- X : Le tir vient de toucher un bateau \n");
	printf("\n");
}

// pour chaque bateau, verifie son l'état du tir
int veriftouche(coord_t cell, matrice_case_t matrice, t_liste batjoueur){
	int touche;
	bateau_t actueltemp;
	en_tete(&batjoueur);
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur,&actueltemp);
		touche = toucheunbateau(matrice, cell, batjoueur);
		if(touche != 0){
			return touche; //si un bateau est touché renvoie 1 s'il est soulement touché, 2 s'il est coulé
		}
		suivant(&batjoueur);
	}
	return touche;
}

// En fonction de la case choisis, renvoie une valeur suivant si le tir touche, coule ou rate
int etat_tir( matrice_case_t matrice , coord_t cell, t_liste batjoueur){
		return veriftouche(cell, matrice, batjoueur);
}


// vérifie si toute la flotte est coulé
int bateaux_coules( t_liste batjoueur, int nb_bat){
	bateau_t bateau;
	int c_bat_coul=0;
	en_tete(&batjoueur);
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur,&bateau);
		c_bat_coul += bat_coul(bateau); //contient le nombre de bateau touché
		suivant(&batjoueur);
	}
	if(c_bat_coul == nb_bat){ //compare avec le nombre de bateau au total
		return 1;
	}
	return 0;
}

//rempli la t_liste de bateau par leur type selon leur taille
int type_bateau(t_liste batjoueur){
	en_tete(&batjoueur);
	bateau_t actuel;
	if(liste_vide(&batjoueur)){//vérifie si la liste est vide
			return 0;
	}
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur, &actuel);
		switch(actuel.taille){ //donne le type en fonction de la taille du bateau
			case 1: modif_type(&actuel, MINE);break;
			case 2: modif_type(&actuel, TORPILLEUR);break;
			case 3: modif_type(&actuel, SOUSMARIN);break;
			case 4: modif_type(&actuel, CROISEUR);break;
			case 5: modif_type(&actuel, PORTEAVION);break;
			default: printf("Erreur dans le type du bateau\n");
		}
		modif_elt(&batjoueur, &actuel);
		suivant(&batjoueur);
	}
	return 1;
}

//copie la liste de bateau du premier t_liste dans le deuxième t_liste
// joueur2 doit etre vide !
int appliquer_bateau(t_liste batjoueur1, t_liste batjoueur2){
		en_tete(&batjoueur1);
		en_tete(&batjoueur2);
		coord_t emp;
		emp.x = -1;
		emp.y = -1;
		dir_t direct;
		direct = AUCUN;
		bateau_t nouveau;
		if(liste_vide(&batjoueur1)){
			return 0;
		}
		while(!hors_liste(&batjoueur1)){
			valeur_elt(&batjoueur1, &nouveau);
			modif_coord(&nouveau, emp); //on modif les coord (réinitilisation)
 			modif_direction(&nouveau, direct); //la direction aussi (réinitilisation)
			ajout_droit(&batjoueur2, nouveau); //on l'ajoute a la liste du 2ème joueur
			suivant(&batjoueur1);
		}
		return 1;
}


//affiche la flotte d'un joueur
void affichage_flotte(t_liste batjoueur, matrice_case_t matrice){
	char c;
	printf("   ");
	for(int k=1; k<=matrice.nbc; k++){
		
		if(k<10){
			printf("%d  ", k );
		}else{
			printf("%d ", k );
		}
	}
	printf("\n");
	for(int i=0; i<matrice.nbl ; i++){
       		for(int j=0; j<matrice.nbc ; j++){
			c = nombre_to_lettre(i);
       			if (j== 0){
       				printf("%c ", c);
       			}
       			switch(matrice.grille[i][j].etat){
				case CASEVIDE : printf("[ ]");break; //si la case n'a jamais été visée
				case CASETOUCHEE : printf("[o]");break; //si la case a été touché
				case BATEAUVIDE : printf("[.]");break; // si la case contient un "bout" de bateau non touché
				case BATEAUTOUCHE : printf("[*]");break; // si la case contient un "bout" de bateau touché
				case BATEAUCOULE : printf("[!]");break; // si la case contient un "bout" de bateau coulé
				default: fprintf(stderr, "Erreur");
				}

			}
			printf("\n");
		}
		printf("\n");
}

/* renvoie un pointeur sur un tableau des cases non disponibles pour poser les bateaux */
void parcours_matrice(t_liste joueur, coord_t* case_nonlibres, matrice_case_t matrice ){
	int compteur=0;
	bateau_t bat;
	int fin_bat;
	coord_t actuel;
	int i;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, &bat);
		if(bat.dir == HORIZONTAL){ //si le bateau est à l'horizontal
	    		fin_bat = fin_bateau_horizontal(&bat);
	     		for(i = bat.coord.y; i <= fin_bat; i++){ //on parcours les y du bateaux (car les x ne changent pas)
       				actuel.y = i;
       				actuel.x=bat.coord.x;
       				if(i==bat.coord.y){ //si on est au début du bateau on remplit des cases situées autour (haut, bas, gauche et diagonal)
						actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.x++;
						case_nonlibres[compteur] = actuel;
						compteur++;
						actuel.x++;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.y--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
		       				actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
					}
					else if(i==fin_bat){ //si on est à la fin, meme chose  (haut, bas, droite et diagonal)
						actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.x++;
						case_nonlibres[compteur] = actuel;
						compteur++;
						actuel.x++;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.y++;
						if(danslagrille_joueur(matrice, actuel)){
								case_nonlibres[compteur] = actuel;
								compteur++;
						}
	       					actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
								case_nonlibres[compteur] = actuel;
								compteur++;
						}
						actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
					}
					else{ //sinon les cases qui l'entoure (haut et bas)
						case_nonlibres[compteur].x =actuel.x ;
						case_nonlibres[compteur].y =actuel.y ;
						actuel.x--;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
						actuel.x++;
						case_nonlibres[compteur] = actuel;
						compteur++;
						actuel.x++;
						if(danslagrille_joueur(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
						}
					}
			}
		}
		else if(bat.dir == VERTICAL){ //si le bateau est placé à la vertical
			fin_bat = fin_bateau_vertical(&bat);
    	  		for(i=bat.coord.x; i<=fin_bat; i++){ //on parcourt le x du bateau(car les y ne changent pas)
      				actuel.x= i;
      				actuel.y=bat.coord.y;
				if(bat.taille == 1){ //si le bateau est de taille 1, on remplit de blanc toutes les cases autour(diagonales,nord,sud,est,ouest)
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
	       				actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x+=2;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
       				else if(i==bat.coord.x){ //si on est au début du bateau on remplit des cases situées autour (gauche, droite, haut et diagonal)
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){ //si on est à la fin, meme chose  (gauche, droite, bas et diagonal)
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{  //sinon les cases qui l'entoure (droite et gauche)
					case_nonlibres[compteur].x = actuel.x ;
					case_nonlibres[compteur].y = actuel.y;
					actuel.y--;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille_joueur(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
			}
		} //else { fprintf(stderr, "ON NE DEVRAIT JAMAIS ETRE LA\n"); }
		suivant(&joueur);
	}
	actuel.x = -1;
	actuel.y = -1;
	case_nonlibres[compteur] = actuel;
}



//applique la direction et les coordonnées du bateau transmis de la t_liste si les cases sont disponibles
int placement_bateau(t_liste batjoueur, bateau_t * bat, dir_t dir, coord_t emp, matrice_case_t matrice){
	int result = 0;
	coord_t upt;
	int fin_bat;
	etat_case_t etat = BATEAUVIDE;
	coord_t *casesprises = malloc(sizeof(coord_t)*matrice.nbl*matrice.nbc);
	parcours_matrice(batjoueur, casesprises,matrice);
	result = verif_placement_bateau(bat, dir, emp, casesprises); //on vérifie si le placement voulu correspond
  	if(result){
    		en_queue(&batjoueur);
    		modif_coord(bat, emp);
    		modif_direction(bat, dir);
	   	ajout_droit(&batjoueur, *bat);
		if(bat->dir == HORIZONTAL){ //si le bateau est à l'horizontal
			upt.x = bat->coord.x;
			fin_bat = fin_bateau_horizontal(bat);
			for(upt.y = bat->coord.y; upt.y <= fin_bat ; upt.y++){
				update_case_mat(matrice, upt , etat); //on modifie les cases de la matrice
			}
		}
		else {//si le bateau est à la vertical
			upt.y = bat->coord.y;
			fin_bat = fin_bateau_vertical(bat);
			for(upt.x=bat->coord.x; upt.x <= fin_bat ; upt.x++){
				update_case_mat(matrice, upt , etat); //on modifie les cases de la matrice
			}
		}
	}
	free(casesprises);
    return result;
}


//demande au joueur,en parcourant la t_liste, où il veut placer le nième bateau, se termine quand il a placé tous les bateaux
void placer_bateau(t_liste bateau_nonplace, t_liste batjoueur, matrice_case_t matrice){
	int dir_donne;
	dir_t direction;
	coord_t emp;
	bateau_t nouv;
	char * nomdutype;
	char c;
	en_tete(&bateau_nonplace);
	for(int i=1;!hors_liste(&bateau_nonplace);){
		valeur_elt(&bateau_nonplace, &nouv);
		//fprintf(stderr, "ELEMENT: type=%s \n", typebat_str(nouv.type));
		nomdutype = typebat_str(nouv.type);
		printf("Vous allez placer le bateau numero %i , il s'agit d'un(e) %s , de taille %i \n", i, nomdutype, nouv.taille);
		if(nouv.taille !=1){
			do{
				printf("Dans quelle direction voulez-vous placer le bateau ? (donnez un entier selon : vertical = 1, horizontal = 2) \n");
				scanf("%i", &dir_donne);
				if(dir_donne ==1){
					direction = VERTICAL;
				}
				else if(dir_donne == 2){
					direction = HORIZONTAL;
				}
				else{
					printf("Mauvaise direction\n");
				}
			}while(dir_donne >2 || dir_donne <1); //Verification
		}else{
			direction = DEFAULT_DIRECTION;
		}
		if(direction == VERTICAL){
			do{
			printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre A et %c) \n Coordonnée lettre  = ", nombre_to_lettre(matrice.nbl));
				scanf("%c", &c);//scanf poubelle
				scanf("%c", &c);
				emp.x = lettre_to_nombre(c);
				emp.x++;
				if(emp.x < 1){
					printf("La ligne n'est pas dans la grille (inférieur à 1) \n");
				}
				else if( emp.x > matrice.nbl){
					printf("La ligne n'est pas dans la grille (supérieur à %c) \n",nombre_to_lettre(matrice.nbl-1));
				}
				else if((emp.x)+(nouv.taille)-1> matrice.nbl){
					printf("La fin du bateau dépasse la grille\n");
				}
			}while(emp.x <1 || emp.x > matrice.nbl || (emp.x)+(nouv.taille)-1> matrice.nbl);

			do{
				printf("\n Coordonnée chiffre = ");
				scanf("%i", &emp.y);
				if(emp.y < 1){
					printf("La colonne n'est pas dans la grille (inférieur à 1) \n");
				}
				else if( emp.y > matrice.nbc){
					printf("La colonne n'est pas dans la grille (supérieur à %i) \n",matrice.nbc);
				}
			}while(emp.y < 1 || emp.y > matrice.nbc ); //Verification
			emp.x -= 1 ;//on décrémente car la matrice va de 0 au nombre de ligne-1
			emp.y -= 1 ;
		}else{
			do{
				printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre A et %c) \n Coordonnée lettre = ", nombre_to_lettre(matrice.nbl));
				scanf("%c", &c);//scanf poubelle
				scanf("%c", &c);
				emp.x = lettre_to_nombre(c);
				emp.x++;
				if(emp.x < 1){
					printf("La ligne n'est pas dans la grille (inférieur à 1) \n");
				}
				else if( emp.x > matrice.nbl){
					printf("La ligne n'est pas dans la grille (supérieur à %c) \n",nombre_to_lettre(matrice.nbl-1));
				}
			}while(emp.x < 1 || emp.x > matrice.nbl); //Verification

			do{
				printf("\n Coordonnée chiffre = ");
				scanf("%i", &emp.y);
				if(emp.y < 1){
					printf("La colonne n'est pas dans la grille (inférieur à 1) \n");
				}
				else if( emp.y > matrice.nbc){
					printf("La colonne n'est pas dans la grille (supérieur à %i) \n",matrice.nbc);
				}
				else if((emp.y)+(nouv.taille)-1> matrice.nbc){
					printf("La fin du bateau dépasse la grille : %i", (emp.x)+(nouv.taille)-1);
				}
			}while(emp.y < 1 || emp.y > matrice.nbc || (emp.y)+(nouv.taille)-1> matrice.nbc);//Verification
			emp.x -= 1 ;//on décrémente car la matrice va de 0 au nombre de ligne-1
			emp.y -= 1 ;
		}
		if(placement_bateau(batjoueur, &nouv, direction, emp, matrice)){ //si le bateau a été passé
			printf("Le bateau a ete place\n"); //on passe au suivant
			suivant(&bateau_nonplace);
			i++;
			affichage_flotte(batjoueur, matrice);
			printf("\n");
		}
		else{
			printf("Le bateau n'a pas pu etre place, veuillez reessayer\n");
		}
	}
}

//demande au premier jouer le nombre de bateau qu'il veut et leur taille et retourne le nombre de bateaux
int choixbateau(t_liste batjoueur, matrice_case_t matrice){
	int nbbat=0;
	int t;
	t_liste bateau_nonplace;
	init_liste(&bateau_nonplace);
	bateau_t nouveau;
	int calcul = (matrice.nbc+matrice.nbl)/2;
	float nbmaxbat = (0.06 * (calcul*calcul)) - (0.3 * calcul) +2;//Calcul du nombre de bateau max selon la taille de la matrice
	while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bateau voulez-vous avoir ? (entre 1 et %0.f) : ", nbmaxbat);
              scanf("%i", &nbbat);
	}
	en_tete(&bateau_nonplace);
        for(int i=1; i<=nbbat;i++){
		do{
			printf("Ecrire la taille du bateau %i (entre 1 et 5) : ",i);
			scanf("%i", &t);
			if(t<=5 && t>=1){
				nouveau_bateau(t, &nouveau);
				ajout_droit(&bateau_nonplace, nouveau);
			}
			else{
				printf("Taille du bateau incorrecte\n");
			}
		}while(t>5 || t<1); //Verification
       }
       type_bateau(bateau_nonplace);
       placer_bateau(bateau_nonplace, batjoueur, matrice);
       return nbbat;
}


//renvoie la taille du bateau le plus petit de la t_liste
int bateau_plus_petit(t_liste batjoueur){
	int min = 5; //le minimum est initiliaser à la taille max possible d'un bateau
	bateau_t actuel;
	en_tete(&batjoueur);
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur, &actuel);
		if(actuel.taille < min){ //si le bateau actuel est plus petit que celui enregisté
			min = actuel.taille; //changer le minimum
		}
		suivant(&batjoueur);
	}
	return min;
}

/* renvoie 2 si le bateau est coulé, 1 s'il est touché et 0 si le tir est dans l'eau*/
int toucheunbateau(matrice_case_t mat, coord_t cell, t_liste batjoueur){
		int fin_bat;
		int i,j;
		coord_t actuel;
		bateau_t actueltemp;
		valeur_elt(&batjoueur, &actueltemp);
		if(actueltemp.dir == VERTICAL){ // si le bateau est a la vertical
			fin_bat = fin_bateau_vertical(&actueltemp);
			for(i = actueltemp.coord.x, j = actueltemp.coord.y; i <= fin_bat; i++){ //on parcours le bateau
				if(cell.x == i && cell.y == j){ //si les coordonnées correspondent
					incrementer_nbtouche(&actueltemp); //on incrémente le nombre de fois que le bateau a été touché
					modif_elt(&batjoueur, &actueltemp);
					if(actueltemp.nb_touche == actueltemp.taille){ // si la taille du bateau correspond au nombre de fois qu'il a été touché
						modif_etat(&actueltemp, COULE); //le bateau est coulé
						modif_elt(&batjoueur, &actueltemp);
						actuel.y = actueltemp.coord.y;
						for(actuel.x = actueltemp.coord.x; actuel.x  <= fin_bat; actuel.x++){ //on modifie la matrice pour que le bateau soit désormais coulé
							update_case_mat(mat, actuel, BATEAUCOULE);
						}
						return 2;
					}
					else{
						update_case_mat(mat, cell, BATEAUTOUCHE);//on modifie la matrice pour que la case du bateau soit désormais touché
						return 1;
					}
				}
			}
		}
		else if(actueltemp.dir == HORIZONTAL){ // si le bateau est a l'horizontal
			fin_bat = fin_bateau_horizontal(&actueltemp);
			for(i = actueltemp.coord.x, j = actueltemp.coord.y; j <= fin_bat; j++){//on parcours le bateau
				if(cell.x== i && cell.y == j){//si les coordonnées correspondent
					incrementer_nbtouche(&actueltemp); //on incrémente le nombre de fois que le bateau a été touché
					modif_elt(&batjoueur, &actueltemp);
					if(actueltemp.nb_touche == actueltemp.taille){// si la taille du bateau correspond au nombre de fois qu'il a été touché
						modif_etat(&actueltemp, COULE); //le bateau est coulé
						modif_elt(&batjoueur, &actueltemp);
						actuel.x = actueltemp.coord.x;
						for(actuel.y = actueltemp.coord.y; actuel.y  <= fin_bat; actuel.y++){ //on modifie la matrice pour que le bateau soit désormais coulé
							update_case_mat(mat, actuel, BATEAUCOULE);
						}
						return 2;
					}
					else{
						update_case_mat(mat, cell, BATEAUTOUCHE); //on modifie la matrice pour que la case du bateau soit désormais touché
						return 1;
					}
				}
			}
		}
		else
			printf("Direction incorrecte\n");

		update_case_mat(mat, cell, CASETOUCHEE);
		return 0;
}
