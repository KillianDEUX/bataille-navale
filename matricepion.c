#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"

matrice_t creer_matrice_adv (int nbl, int nbc){

	matrice_t mat;
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

void detruire_matrice_adv( matrice_t mat){
	free(mat.grille[0]);
	free(mat.grille);
}


int init_matrice_adv(matrice_t mat){

	for(int i=0; i<mat.nbl ; i++){
       	for(int j=0; j<mat.nbc ; j++){
           	mat.grille[i][j].c= AUCUNE;
        }
	}
	return 0;
}



int danslagrille(matrice_t mat, coord_t pos ){

	if( pos.x >= mat.nbl || pos.y >= mat.nbc || pos.x < 1 || pos.y < 1 )
		return 0;
	return 1;
}


void eauautourcoule( coord_t cell, matrice_t mat ){
	// Lorsque le bateau est dirigé vers le nord
	coord_t celltemp;
	celltemp.x=cell.x+1;
	celltemp.y=cell.y;
	if ( danslagrille(mat, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(taille, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y++;
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	celltemp.y=cell.y-1; 									// Changement
	celltemp.x=cell.x;
	if ( danslagrille(taille, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(taille, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					(mat.grille[celltemp.x][celltemp.y]).c= BLANC;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y--;                   					// Changement
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	celltemp.y=cell.y;                   				                        // Changement
	celltemp.x=cell.x+1;                 					                // Changement
	if ( danslagrille(taille, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(taille, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.y=cell.y+1;							// Changement
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y=cell.y-1;							// Changement
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x++;							// Changement
			}
			celltemp.y=cell.y+1;								// Changement
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y-1;								// Changement
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y;								// Changement
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	celltemp.y=cell.y;
	celltemp.x=cell.x-1;                  					                // Changement
	if ( danslagrille(taille, celltemp)){
		if( mat.grille[celltemp.x][celltemp.y].c== AUCUNE){
			mat.grille[celltemp.x][celltemp.y].c= BLANC;
		}else if (mat.grille[celltemp.x][celltemp.y].c== ROUGE){
			while((danslagrille(taille, celltemp)) && (mat.grille[celltemp.x][celltemp.y].c== ROUGE)){
				celltemp.y=cell.y+1;
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.y=cell.y-1;
				if(danslagrille(taille, celltemp)){
					mat.grille[celltemp.x][celltemp.y].c= BLANC;
				}
				celltemp.x--;							// Changement
			}
			celltemp.y=cell.y+1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y-1;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
			celltemp.y=cell.y;
			if(danslagrille(taille, celltemp)){
				mat.grille[celltemp.x][celltemp.y].c= BLANC;
			}
		}
	}
}



int ajout_pion_matrice( case_t cell, matrice_t mat, t_liste actuel ){

	if( etat_tir(cell, mat, actuel)==0){        			// Si le tir tombe dans l'eau
		(mat.grille[cell.x][cell.y]).c= BLANC ;    				// Placer un pion BLANC sur la matrice
	}else if( etat_tir(cell, mat, actuel)==1){  			 // Si le tir touche une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ;    			   // Placer un pion ROUGE sur la matrice
	}else if( etat_tir(cell, mat, actuel)==2){	 		// Si le tir coule une cible
		(mat.grille[cell.x][cell.y]).c= ROUGE ; 				 // Placer un pion ROUGE sur la matrice
		eauautourcoule(cell, mat);       		 // Placer des pion BLANCs tout autour sur la matrice
	}else{
		return 1;
	}
	return 0;
}


int vider_matrice(matrice_t mat){
	int i=init_matrice_adv( mat );
	return i;
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_pion( matrice_t mat){
	for(int i=0; i<mat.nbl ; i++){
       		for(int j=0; j<mat.nbc ; j++){
           		if(mat.grille[i][j].c == AUCUNE){
				printf(". ");
			}else if(mat.grille[i][j].c == BLANC){
				printf("0 ");
			}else{
				printf("X ");
			}
		}
		printf("\n");
	}
}
