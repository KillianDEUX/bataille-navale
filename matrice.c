#include <stdio.h>
#include <stdlib.h>
#include "matricepion.h"
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

// creer la grille joueur en fonction des choix du joueur précédemment récupérer
matrice_case_t choixplateau(matrice_case_t mat_case, matrice_pion_t mat_pion){	
	int nbli = mat_pion.nbl;
	int nbco = mat_pion.nbc;
	mat_case = creer_matrice_joueur(nbli, nbco);
	return mat_case;
}

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







