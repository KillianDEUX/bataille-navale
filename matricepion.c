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

	if( pos.x >= mat.nbl || pos.y >= mat.nbc || pos.x < 1 || pos.y < 1 )
		return 0;
	return 1;
}

// Ajoute des pions Blancs autour d'un bateau coulé
void eauautourcoule( coord_t cell, matrice_pion_t mat ){
	// Lorsque le bateau est dirigé vers le nord
	coord_t celltemp;
	celltemp.x=cell.x+1;
	celltemp.y=cell.y;
	if ( danslagrille(mat, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(mat, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.x=cell.x+1;
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y++;
			}
			celltemp.x=cell.x+1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	celltemp.y=cell.y-1; 									// Changement
	celltemp.x=cell.x;
	if ( danslagrille(mat, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(mat, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.x=cell.x+1;
				if(danslagrille(mat, celltemp)){
					(mat.grille[celltemp.x][celltemp.y]).c= BLANC;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y--;                   					// Changement
			}
			celltemp.x=cell.x+1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	celltemp.y=cell.y;                   				                        // Changement
	celltemp.x=cell.x+1;                 					                // Changement
	if ( danslagrille(mat, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(mat, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.y=cell.y+1;							// Changement
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y=cell.y-1;							// Changement
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x++;							// Changement
			}
			celltemp.y=cell.y+1;								// Changement
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y-1;								// Changement
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y;								// Changement
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	celltemp.y=cell.y;
	celltemp.x=cell.x-1;                  					                // Changement
	if ( danslagrille(mat, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(mat, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.y=cell.y+1;
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y=cell.y-1;
				if(danslagrille(mat, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x--;							// Changement
			}
			celltemp.y=cell.y+1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y-1;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y;
			if(danslagrille(mat, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
}


	// Ajoute un pion à la gille suivant le tir
int ajout_pion_matrice( coord_t cell, matrice_case_t mat_case, matrice_pion_t mat, t_liste joueur ){

  int etat=etat_tir( mat_case,cell, joueur);
	if( etat == 0){        														// Si le tir tombe dans l'eau
		(mat.grille[cell.x][cell.y]).c= BLANC ;    				// Placer un pion BLANC sur la matrice
	}else if( etat == 1){  														 // Si le tir touche une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ;    			   // Placer un pion ROUGE sur la matrice
	}else if( etat == 2){	 														// Si le tir coule une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ; 				 // Placer un pion ROUGE sur la matrice
		eauautourcoule(cell, mat);       							 // Placer des pion BLANCs tout autour sur la matrice
	}else{
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
