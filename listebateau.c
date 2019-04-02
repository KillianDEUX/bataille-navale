#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"
#include "matrice.h"
#include "bateau.h"

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
		touche=toucheunbateau(cell, &actueltemp);
		if(touche!=0){
			return touche;
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
	while(!hors_liste(&batjoueur)){
		valeur_elt(&batjoueur,&bateau);
		c_bat_coul+=bat_coul(bateau);
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
		fprintf(stderr, "DEBUG: la boucle se fait\n");
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
		bateau_t nouveau;
		if(liste_vide(&batjoueur1)){
			return 0;
		}
		while(!hors_liste(&batjoueur1)){
			valeur_elt(&batjoueur1, &nouveau);
			ajout_droit(&batjoueur2, nouveau);
			suivant(&batjoueur1);
			suivant(&batjoueur2);
		}
		return 1;
}


//affiche la flotte d'un joueur
void affichage_flotte(t_liste batjoueur, matrice_case_t matrice){
	bateau_t actuel;
	for(int i=1; i<=matriceF.nbl ; i++){
       		for(int j=1; j<=matrice.nbc ; j++){
       			en_tete(&batjoueur);
       			while(!hors_liste(&batjoueur)){
       				valeur_elt(&batjoueur, &actuel);
       				afficher_bateau(actuel, i, j);
	       			suivant(&batjoueur);
	       		}
       		}
		printf("\n");
	}
}

/* renvoie un pointeur sur un tableau des cases non disponibles pour poser les bateaux */
void parcours_matrice(t_liste joueur, coord_t* case_nonlibres, matrice_case_t matrice ){
	bateau_t bat;
	int fin_bat;
	int i, compteur=0;
	coord_t actuel;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, &bat);
		if(bat.dir == VERTICAL){
	       		fin_bat = fin_bateau_vertical(&bat);
	       		for(i=bat.coord.y;i<=fin_bat; i++){
       				actuel.x=bat.coord.x;
       				actuel.y=bat.coord.y;
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
		else if(bat.dir == HORIZONTAL){
			fin_bat = fin_bateau_horizontal(&bat);
       			for(i=bat.coord.x;i<=fin_bat; i++){
       				actuel.x=bat.coord.x;
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
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ;
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
	coord_t *casesprises = malloc(sizeof(coord_t)*matrice.nbl*matrice.nbc);
	parcours_matrice(batjoueur, casesprises,matrice);
	result = verif_placement_bateau(bat, emp, casesprises);
    if(result){
    		en_queue(&batjoueur);
    		modif_coord(bat, emp);
    		modif_direction(bat, dir);
	    	ajout_droit(&batjoueur, *bat);
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
		fprintf(stderr, "ELEMENT: type=%s, coord=(%d,%d) \n", typebat_str(nouv.type), nouv.coord.x, nouv.coord.y);
		
		nomdutype = typebat_str(nouv.type);
		printf("Vous allez placer le bateau numero %i , il s'agit d'un(e) %s , de taille %i \n", i, nomdutype, nouv.taille);
		do{
			printf("Dans quelle direction voulez-vous placer le bateau ?(donner un entier selon : vertical = 1, horizontal = 2) \n");
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
		if(direction == VERTICAL){
			do{
				printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x <1 || emp.x > matrice.nbc);
			
			do{
				printf("\n y = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbl);
		}else{
			do{
				printf("Quelles sont les coordonnees a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x <1 || emp.x > matrice.nbl);
		
			do{
				printf("\n y = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbc);
		}
			
		if(placement_bateau(batjoueur, &nouv, direction, emp, matrice)){
			printf("Le bateau a ete place\n");
			suivant(&bateau_nonplace);
			i++;
		}
		else{
			printf("Le bateau n'a pas pu etre place, veuillez reessayer\n");
		}
	}
}

//demande au premier jouer le nombre de bateau qu'il veut et leur taille
void choixbateau(t_liste batjoueur, matrice_case_t matrice){
       int nbbat=0;
       int t;
       t_liste bateau_nonplace;
       init_liste(&bateau_nonplace);
       bateau_t nouveau;
       float nbmaxbat = (0.06 * (matrice.nbc*matrice.nbl)) - (0.3 * matrice.nbl) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bateau voulez-vous avoir ?(différent de 0 et inférieur à %0.f) : ", nbmaxbat);
              scanf("%i", &nbbat);
       }
	   en_tete(&bateau_nonplace);
       for(int i=1; i<=nbbat;i++){
       		  do{
		          printf("Ecrire la taille du bateau %i(entre 1 et 5) : ",i);
		          scanf("%i", &t);
		          if(t<=5 && t>=1){
		                 nouveau_bateau(t, &nouveau);
		                 ajout_droit(&bateau_nonplace, nouveau);
		                 fprintf(stderr, "DEBUG: implementation bateau\n");
		          }
		          else{printf("Taille du bateau incorrecte");}
		   }while(t>5 || t<1);
       }
       type_bateau(bateau_nonplace);
       placer_bateau(bateau_nonplace, batjoueur, matrice);
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




