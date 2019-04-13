#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"
#include "matrice.h"
#include "bateau.h"

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




// pour chaque bateau, verifie son l'état du tir
int veriftouche(coord_t cell, matrice_case_t matrice, t_liste batjoueur){
	int touche;
	bateau_t actueltemp;
	en_tete(&batjoueur);
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur,&actueltemp);
		touche = toucheunbateau(matrice, cell, batjoueur);
		if(touche != 0){
			fprintf(stderr, "je suis dans veritouche, renvoie : %i \n", touche);
			return touche;
		}
		suivant(&batjoueur);
	}
	fprintf(stderr, "je suis dans veritouche, renvoie : %i \n", touche);
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
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur,&bateau);
		c_bat_coul+=bat_coul(bateau);
		fprintf(stderr, "bat :%i\n", c_bat_coul );
		suivant(&batjoueur);
	}
	if(c_bat_coul==nb_bat){
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
		switch(actuel.taille){
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
			modif_coord(&nouveau, emp);
 			modif_direction(&nouveau, direct);
			ajout_droit(&batjoueur2, nouveau);
			suivant(&batjoueur1);
		}
		return 1;
}


//affiche la flotte d'un joueur
void affichage_flotte(t_liste batjoueur, matrice_case_t matrice){
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
       			if (j== 0){
       				if((i+1)<10){
						printf("%d ", i+1);
					}else{
						printf("%d", i+1);
					}
       			}
       			switch(matrice.grille[i][j].etat){
				case CASEVIDE : printf("[ ]");break;
				case CASETOUCHEE : printf("[o]");break;
				case BATEAUVIDE : printf("[.]");break;
				case BATEAUTOUCHE : printf("[*]");break;
				case BATEAUCOULE : printf("[!]");break;
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
		if(bat.dir == HORIZONTAL){
	    	fin_bat = fin_bateau_horizontal(&bat);
	     	for(i = bat.coord.y; i <= fin_bat; i++){
       			actuel.y = i;
       			actuel.x=bat.coord.x;
       			if(i==bat.coord.y){
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
					else if(i==fin_bat){
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
					else{
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
		else if(bat.dir == VERTICAL){
			fin_bat = fin_bateau_vertical(&bat);
    	  	for(i=bat.coord.x; i<=fin_bat; i++){
      			actuel.x= i;
      			actuel.y=bat.coord.y;
       			if(i==bat.coord.x){
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
				else if(i==fin_bat){
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
				else{
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
	result = verif_placement_bateau(bat, dir, emp, casesprises);
  	if(result){
    	en_queue(&batjoueur);
    	modif_coord(bat, emp);
    	modif_direction(bat, dir);
	    ajout_droit(&batjoueur, *bat);
		if(bat->dir == HORIZONTAL){
			upt.x = bat->coord.x;
			fin_bat = fin_bateau_horizontal(bat);
			for(upt.y = bat->coord.y; upt.y <= fin_bat ; upt.y++){
				update_case_mat(matrice, upt , etat);
			}
		}
		else {//if(bat->dir == VERTICAL){;
			upt.y = bat->coord.y;
			fin_bat = fin_bateau_vertical(bat);
			for(upt.x=bat->coord.x; upt.x <= fin_bat ; upt.x++){
				update_case_mat(matrice, upt , etat);
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
			}while(dir_donne >2 || dir_donne <1);
		}else{
			direction = DEFAULT_DIRECTION;
		}
		if(direction == VERTICAL){
			do{
				printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n Numéro de ligne = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x <1 || emp.x > matrice.nbl || (emp.x)+(nouv.taille)-1> matrice.nbl);

			do{
				printf("\n Numéro de colonne = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbc );
			emp.x -= 1 ;
			emp.y -= 1 ;
		}else{
			do{
				printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n Numéro de ligne = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x < 1 || emp.x > matrice.nbl);

			do{
				printf("\n Numéro de colonne = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbc || (emp.y)+(nouv.taille)-1> matrice.nbc);
			emp.x -= 1 ;
			emp.y -= 1 ;
		}
		if(placement_bateau(batjoueur, &nouv, direction, emp, matrice)){
			printf("Le bateau a ete place\n");
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
       float nbmaxbat = (0.06 * (calcul*calcul)) - (0.3 * calcul) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bateau voulez-vous avoir ? (différent de 0 et inférieur à %0.f) : ", nbmaxbat);
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
		          else{printf("Taille du bateau incorrecte");}
		   }while(t>5 || t<1);
       }
       type_bateau(bateau_nonplace);
       placer_bateau(bateau_nonplace, batjoueur, matrice);
       return nbbat;
}


//renvoie la taille du bateau le plus petit de la t_liste
int bateau_plus_petit(t_liste batjoueur){
	int min = 5;
	bateau_t actuel;
	en_tete(&batjoueur);
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur, &actuel);
		if(actuel.taille < min){
			min = actuel.taille;
		}
		suivant(&batjoueur);
	}
	return min;
}

/* renvoie 2 si le bateau est coulé, 1 s'il est touché et 0 si le tir est dans l'eau*/
int toucheunbateau(matrice_case_t mat, coord_t cell, t_liste batjoueur){
		int fin_bat;
		int i,j;
		bateau_t actueltemp;
		valeur_elt(&batjoueur, &actueltemp);
		if(actueltemp.dir == VERTICAL){
			fin_bat = fin_bateau_vertical(&actueltemp);
			for(i = actueltemp.coord.x, j = actueltemp.coord.y; i <= fin_bat; i++){
				if(cell.x== i && cell.y == j){
					printf("touche avant : %i \n", actueltemp.nb_touche);
					incrementer_nbtouche(&actueltemp);
					modif_elt(&batjoueur, &actueltemp);
					fprintf(stderr, "nb touche = %i, taille = %i \n",actueltemp.nb_touche, actueltemp.taille );
					if(actueltemp.nb_touche == actueltemp.taille){
						modif_etat(&actueltemp, COULE);
						update_case_mat(mat, cell, BATEAUCOULE);
						return 2;
					}
					else{
						update_case_mat(mat, cell, BATEAUTOUCHE);
						return 1;
					}
				}
			}
		}
		else if(actueltemp.dir == HORIZONTAL){
			fin_bat = fin_bateau_horizontal(&actueltemp);
			for(i = actueltemp.coord.x, j = actueltemp.coord.y; j <= fin_bat; j++){
				if(cell.x== i && cell.y == j){
					printf("touche avant : %i \n", actueltemp.nb_touche);
					incrementer_nbtouche(&actueltemp);
					modif_elt(&batjoueur, &actueltemp);
					fprintf(stderr, "nb touche = %i, taille = %i \n",actueltemp.nb_touche, actueltemp.taille );
					if(actueltemp.nb_touche == actueltemp.taille){
						modif_etat(&actueltemp, COULE);
						update_case_mat(mat, cell, BATEAUCOULE);

						return 2;
					}
					else{
						update_case_mat(mat, cell, BATEAUTOUCHE);
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
