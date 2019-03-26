#include <stdio.h>
#include <stdlib.h>
#include "matricepion.h"


// creer la grille en fonction des choix du joueur
matrice_t choixgrille(matrice_t mat){
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
