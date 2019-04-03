#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"



// Creer une matrice de taille nbl sur nbc et lui alloue de la mémoire
matrice_case_t creer_matrice_joueur(int nbl, int nbc){

	matrice_case_t mat;
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
void detruire_matrice_joueur( matrice_case_t mat){
	free(mat.grille[0]);
	free(mat.grille);
}

// initialise la matrice avec "CASEVIDE";
int init_matrice_joueur(matrice_case_t mat){

	for(int i=0; i<mat.nbl ; i++){
       	for(int j=0; j<mat.nbc ; j++){
           	mat.grille[i][j].etat = CASEVIDE;
        }
	}
	return 0;
}

void update_case_mat(matrice_case_t mat, coord_t cell, etat_case_t etat){
	mat.grille[cell.x][cell.y].etat = etat;
}




// Vérifie si les coordonnées passées en paramètres sont dans la grille
int danslagrille_joueur(matrice_case_t mat, coord_t pos ){

	if( pos.x >= mat.nbl || pos.y >= mat.nbc || pos.x < 1 || pos.y < 1 )
		return 0;
	return 1;
}







