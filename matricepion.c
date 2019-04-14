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
		printf("Quelle largeur de la grille souhaitez-vous ? (entre 5 et 32)\n");
		scanf("%d",&nbco);
		if(nbco<5 || nbco>32){
			printf("Largeur de la grille non conforme\n");
		}
	}while(nbco<5 || nbco>32);
	do{
		printf("Quelle hauteur de la grille souhaitez-vous ?(entre 5 et 32)\n");
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
	if(bat.taille == 0){
		fprintf(stderr, "Erreur");
	}
	else{
		if(bat.dir == VERTICAL){ //si le bateau est à la verticale
			fin_bat = fin_bateau_vertical(&bat);
			for(int i = bat.coord.x;  i <= fin_bat; i++){  //on parcourt le x du bateau(car les y ne changent pas)
				celltemp.y = bat.coord.y;
				celltemp.x = i;
				if(bat.taille == 1){ //si le bateau est de taille 1, on remplit de blanc toutes les cases autour(diagonales,nord,sud,est,ouest)
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
					celltemp.x+=2;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.y++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else if(celltemp.x == bat.coord.x){ //si on est au début du bateau on remplit de blanc les cases situées autour (gauche, droite, haut et diagonal)
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
				else if(celltemp.x == fin_bat){  //si on est à la fin, meme chose  (gauche, droite, bas et diagonal)
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
				else{ //sinon les cases qui l'entoure (droite et gauche)
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
		else if(bat.dir == HORIZONTAL){//si le bateau est à l'horizontal
			fin_bat = fin_bateau_horizontal(&bat);
			for(int i = bat.coord.y; i <= fin_bat; i++){ //on parcours les y du bateaux (car les x ne changent pas)
				celltemp.y = i;
				celltemp.x = bat.coord.x;
       				if(celltemp.y == bat.coord.y){ //si on est au début du bateau on remplit de blanc les cases situées autour (haut, bas, gauche et diagonal)
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
				else if(celltemp.y == fin_bat){ //si on est à la fin, meme chose  (haut, bas, droite et diagonal)
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
	       				celltemp.x++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
							mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x++;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
				}
				else{ //sinon les cases qui l'entoure (haut et bas)
					celltemp.x--;
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c!= ROUGE){
						mat.grille[celltemp.x][celltemp.y].c= BLANC;
					}
					celltemp.x+=2;
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
	coord_t celltemp;
	nouveau_bateau(0, &erreur);
	int fin_bat;
	int i, j;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){ //parcours de la liste
		valeur_elt(&joueur, &bat);
		if(bat.dir == VERTICAL){ //si le bateau est à la verticale
			fin_bat = fin_bateau_vertical(&bat);
			for(i = bat.coord.x; i <= fin_bat; i++){  //parcours du bateau
				celltemp.y = bat.coord.y;
				celltemp.x = i;
				if(celltemp.x == cell.x && celltemp.y == cell.y){ //si les coordonnées correspondent 
					return bat; //on renvoit le bateau
				}
			}
		}
		else if(bat.dir == HORIZONTAL){ //si le bateau est à l'horizontale
			fin_bat = fin_bateau_horizontal(&bat);
			for(j = bat.coord.y; j <= fin_bat; j++){ //parcours du bateau
				celltemp.y = j;
				celltemp.x = bat.coord.x;
				if(cell.x == celltemp.x && cell.y == celltemp.y){ //si les coordonnées correspondent
					return bat; //on renvoit le bateau
				}
			}
		}
		suivant(&joueur);
	}
	fprintf(stderr,"Ne correspond à aucun bateau : anormal");
	return erreur;
}



// Ajoute un pion à la grille suivant le tir
int ajout_pion_matrice( coord_t cell, matrice_case_t mat_case, matrice_pion_t mat, t_liste joueur){

  	int etat=etat_tir( mat_case,cell, joueur);
	if( etat == 0){        					// Si le tir tombe dans l'eau
		(mat.grille[cell.x][cell.y]).c= BLANC ;    	// Placer un pion BLANC sur la matrice
		printf("\n         RATÉ        \n\n");
	}
	else if( etat == 1){  					// Si le tir touche une cible
		printf("\n         TOUCHÉ      \n\n");
		(mat.grille[cell.x][cell.y]).c= ROUGE ;    	// Placer un pion ROUGE sur la matrice
	}
	else if( etat == 2){	 				// Si le tir coule une cible
		printf("\n         COULÉ       \n\n");
		mat.grille[cell.x][cell.y].c= ROUGE ; 	// Placer un pion ROUGE sur la matrice
		eauautourcoule(cell, mat, joueur);      	// Placer des pion BLANCs tout autour sur la matrice
	}
	else{
		return 1;
	}
	return 0;
}

// Remet tout les pions à "AUCUN"
int vider_matrice(matrice_pion_t mat){
	int i = init_matrice_adv( mat );
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
