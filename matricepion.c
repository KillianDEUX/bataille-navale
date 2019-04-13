#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"


// creer la grille pion en fonction des choix du joueur
matrice_pion_t choixgrille(matrice_pion_t mat){
	int nbli,nbco; // taille de la grille de jeu (nb de lignes/ nb de colonnes)
	do{
		printf("Quel est la largeur de la grille (entre 5 et 32)\n");
		scanf("%d",&nbco);
		if(nbco<5 || nbco>32){
			printf("Largeur de la grille non conforme\n");
		}
	}while(nbco<5 || nbco>32);
	do{
		printf("Quel est la hauteur de la grille (entre 5 et 32)\n");
		scanf("%d",&nbli);
		if(nbli<5 || nbli>32){
			printf("Hauteur de la grille non conforme\n");
		}
	}while(nbli<5 || nbli>32); // pour une taille max de grille de 1024
	mat=creer_matrice_adv(nbli, nbco);
	return mat;
}

// Creer une matrice de taille nbl sur nbc et lui alloue de la mémoire
matrice_pion_t creer_matrice_adv (int nbl, int nbc){

	matrice_pion_t mat;
	mat.nbl = nbl;
	mat.nbc = nbc;

	mat.grille = malloc(nbl * sizeof(*mat.grille));
	if(mat.grille == NULL){
		fprintf(stderr, "Code erreur : manque de mémoire");
	}
	mat.grille[0]= malloc(nbl * nbc * sizeof(**mat.grille));
	if(mat.grille[0]== NULL){
		fprintf(stderr, "Code erreur : manque de mémoire");
	}
	for(int i=1; i<nbl ; i++){
		mat.grille[i]= mat.grille[i-1]+nbc;
	}
	return mat;
}

// Libère la mémoire de la matrice 
void detruire_matrice_adv( matrice_pion_t mat){
	free(mat.grille[0]);
	free(mat.grille);
}

// initialise la matrice avec "AUCUNE" couleur;
int init_matrice_adv(matrice_pion_t mat){

	for(int i=0; i<mat.nbl ; i++){
       	for(int j=0; j<mat.nbc ; j++){
           	mat.grille[i][j].c= AUCUNE;
        }
	}
	return 0;
}


// Vérifie si les coordonnées passées en paramètres sont dans la grille
int danslagrille(matrice_pion_t mat, coord_t pos ){

	if( pos.x >= mat.nbl || pos.y >= mat.nbc || pos.x < 0 || pos.y < 0 )
		return 0;
	return 1;
}

// Ajoute des pions Blancs autour d'un bateau coulé
void eauautourcoule( coord_t cell, matrice_pion_t mat, t_liste joueur){
	bateau_t bat;
	coord_t celltemp;
	int fin_bat;
	bat = recherche_bat(cell, joueur);
	printf("bat : %i %i \n", bat.coord.x, bat.coord.y);
	if(bat.taille == 0){
		fprintf(stderr, "Erreur");
	}
	else{
		if(bat.dir == VERTICAL){
			fin_bat = fin_bateau_vertical(&bat);
			fprintf(stderr, " fin bat = %i",fin_bat );
			celltemp.y = bat.coord.y;
			for(celltemp.x = bat.coord.x;  celltemp.x <= fin_bat; celltemp.x++){
				fprintf(stderr, "boucle verti\n");
				fprintf(stderr, " celltemp : %i %i ", celltemp.x, celltemp.y);
				if(celltemp.x == bat.coord.x){
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y+=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
	       				celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else if(celltemp.x == fin_bat){
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y+=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
	       				celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else{
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y+=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
			}
		}
		else if(bat.dir == HORIZONTAL){
			fin_bat = fin_bateau_horizontal(&bat);
			celltemp.x = bat.coord.x;
			for(celltemp.y = bat.coord.y; celltemp.y <= fin_bat; celltemp.y++){
				fprintf(stderr, "boucle horti \n");
       				if(celltemp.y == bat.coord.y){
					celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x+=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
		       			celltemp.x--;
					if(danslagrille(mat, celltemp)  && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x--;
					if(danslagrille(mat, celltemp)  && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else if(celltemp.y == fin_bat){
					celltemp.x++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x-=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
	       				celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
							mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else{
					celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x += 2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
			}
		}
	}
}

//Renvoie la bateau auquel la coordonnée transmise appartient
bateau_t recherche_bat(coord_t cell, t_liste joueur){
	bateau_t bat;
	bateau_t erreur;
	nouveau_bateau(0, &erreur);
	int fin_bat;
	int i, j;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, &bat);
		if(bat.dir == VERTICAL){
			fin_bat = fin_bateau_vertical(&bat);
			for(i = bat.coord.x, j = bat.coord.y; i <= fin_bat; i++){
				fprintf(stderr, "boucle verti recherche \n");
				if(cell.x == i && cell.y == j){
					return bat;
				}
			}
		}
		else if(bat.dir == HORIZONTAL){
			fin_bat = fin_bateau_horizontal(&bat);
			for(i = bat.coord.x, j = bat.coord.y; j <= fin_bat; j++){
				fprintf(stderr, "boucle hori recherche \n");
				if(cell.x == i && cell.y == j){
					return bat;
				}
			}
		}
	}
	printf("pas normal");
	return erreur;
}



// Ajoute un pion à la grille suivant le tir
int ajout_pion_matrice( coord_t cell, matrice_case_t mat_case, matrice_pion_t mat, t_liste joueur, t_liste joueur_attaque ){

  int etat=etat_tir( mat_case,cell, joueur);
	if( etat == 0){        														// Si le tir tombe dans l'eau
		(mat.grille[cell.x][cell.y]).c= BLANC ;    				// Placer un pion BLANC sur la matrice
	}
	else if( etat == 1){  														 // Si le tir touche une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ;    			   // Placer un pion ROUGE sur la matrice
	}
	else if( etat == 2){	 														// Si le tir coule une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ; 				 // Placer un pion ROUGE sur la matrice
		eauautourcoule(cell, mat, joueur_attaque);       							 // Placer des pion BLANCs tout autour sur la matrice
	}
	else{
		return 1;
	}
	return 0;
}

// Remet tout les pions à "AUCUN"
int vider_matrice(matrice_pion_t mat){
	int i=init_matrice_adv( mat );
	return i;
}

// Voir avec la SDL. Ici affichage version terminal
void afficher_matrice_pion( matrice_pion_t mat){
	printf("   ");
	for(int k=1; k<=mat.nbc; k++){
		if(k<10){
			printf("%d  ", k );
		}else{
			printf("%d ", k );
		}
	}
	printf("\n");
	for(int i=0; i<mat.nbl ; i++){
       		for(int j=0; j<mat.nbc ; j++){
       			if (j== 0){
       				if((i+1)<10){
						printf("%d  ", i+1);
					}else{
						printf("%d ", i+1);
					}
       			}
           		if(mat.grille[i][j].c == AUCUNE){
				printf(".  ");
			}else if(mat.grille[i][j].c == BLANC){
				printf("0  ");
			}else{
				printf("X  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}
