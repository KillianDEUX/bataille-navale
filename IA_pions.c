#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "liste.h"
#include "matricepion.h"
#include "listebateau.h"
#include "direction.h"
#include "commun.h"


// transforme un numéro de case en coordonnées x,y
coord_t case_tabtocoord(matrice_pion_t mat, int nb){
	coord_t cellule;
	if(nb%mat.nbc == 0){ //si on est en bout de colonne
		cellule.y = mat.nbc-1;
	}
	else{
		cellule.y = (nb%mat.nbc)-1;
	}
	if(nb%mat.nbl == 0){ //si on est en bout de ligne
		cellule.x = (nb/mat.nbc)-1;
	}
	else{
		cellule.x = nb/mat.nbc;
	}	
	return cellule;
}

// transforme des coordonnées x,y en numéro de case
int case_coordtotab(matrice_pion_t mat, coord_t cellule){
	int nb;
	nb = ((cellule.x*mat.nbc) + cellule.y)+1;
	return nb;
}

// Verifie si l'IA peut placer un pion à l'endoit cellule
int autorisation_case(matrice_pion_t mat, coord_t cellule){
	if( danslagrille(mat, cellule) && mat.grille[cellule.x][cellule.y].c != AUCUNE){
		return 0;
	}
	return 1;
}

// Place un pion de manière pseudo aleatoire
coord_t pseudo_aleatoire( matrice_pion_t mat, int pluspetitbat){
	srand(time(NULL));
	coord_t cellule;
	int case_alea=rand()%((mat.nbl*mat.nbc));
	cellule= case_tabtocoord( mat, case_alea);
	while((case_alea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE){
		case_alea=rand()%((mat.nbl*mat.nbc));
	}
	cellule= case_tabtocoord( mat , case_alea);
	return cellule;
}

// Verifie si l'IA peut placer un pion à l'endoit cellule
int pseudo_aleatoire_autorisation( matrice_pion_t mat, int pluspetitbat){
	int i;
	srand(time(NULL));
	coord_t cellule;
	int case_alea=rand()%((mat.nbl*mat.nbc));
	cellule= case_tabtocoord( mat, case_alea);
	for(i=0;((case_alea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE) || i<100;i++){ // test sur 100 valeurs
 		case_alea=rand()%((mat.nbl*mat.nbc));
		cellule= case_tabtocoord( mat, case_alea);
	}
	if(i>99){ // si l'IA n'arrive pas à placer son pion au bout de 100 essais, il considère qu'il ne peut pas placer de pions de cette manière
		return 0;
	}
		return  1;
}

// Place un pion de manière completement aleatoire
coord_t aleatoire( matrice_pion_t mat){
	srand(time(NULL));
	coord_t cellule;
	int case_alea=rand()%((mat.nbl*mat.nbc)); //choix d'un chiffre de la matrice aléatoire
	cellule= case_tabtocoord( mat, case_alea); //le transforme en coordonnée
	while(mat.grille[cellule.x][cellule.y].c!=AUCUNE ){
		case_alea=rand()%((mat.nbl*mat.nbc));
	}
	cellule= case_tabtocoord( mat, case_alea); //le transforme en coordonnée
	return cellule;
}

// Choisis une case éloignés de toutes les autres
coord_t est_autour( matrice_pion_t mat){

	float compt=0;
	int totalcase;
	float moit_case;
	int k=0;
	coord_t cell;
	for(int i=0;i<mat.nbl;i++){ //parcours des x de la matrice
		for(int j=0; j<mat.nbc;j++){//parcours des y de la matrice
			if(mat.grille[i][j].c != AUCUNE){ 
				 cell.x = i;
				 cell.y = j;
				 compt += case_coordtotab(mat, cell); //compte le nombre de case vide
				 k++;
			}
		}
	}
	totalcase = mat.nbc * mat.nbl;
	moit_case = totalcase/2;
	compt /= k;
	if(compt > moit_case){
		compt /= 2;
	}
	else if(compt < moit_case){
		compt *= 2;
	}
	//si compt == totalcase/2 compt ne change pas

	if(compt > totalcase){
		cell.x = -1;
		cell.y = -1;
		return cell;
	}
	cell = case_tabtocoord(mat, compt);
	return cell;
}


/* vérifie si un bateau est touché quelque part, et essaye de viser une case qui est à coté */
coord_t detection_touche (matrice_pion_t mat){
	int ca=1;
	coord_t celltemp;
	coord_t cell;
	for( cell.x=0; cell.x<mat.nbl ; cell.x++){ //parcours des x de la matrice
       		for(cell.y=0; cell.y<mat.nbc ; cell.y++){//parcours des y de la matrice
			if(mat.grille[cell.x][cell.y].c==ROUGE){ 
				for(int i=0, dir = direction_debut(); i<=4 ; i++, dir = direction_suivante(dir)){ //parcours des 4 directions
					celltemp=direction_avancer(dir, cell, ca ); //on avance celltemp d'un pas vers la direction actuelle
					while(danslagrille(mat,celltemp) && mat.grille[celltemp.x][celltemp.y].c==ROUGE){ //tant que les cases sont rouges
						ca++; //on incrémente la pas
                  				celltemp = direction_avancer( dir, cell, ca );//on avance celltemp de ca pas vers la direction actuelle
               				}
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c==AUCUNE){ //si il n'y a pas de couleur
						return celltemp; //choisir cette case 
					}
					ca = 1;
				}
			}
   		}
	}
	celltemp.x =-1;
	celltemp.y =-1;
	return celltemp;
}

// Choisis une case de la façon la plus adapté
coord_t choisir_case(matrice_pion_t mat, t_liste joueur){
	coord_t cell;
	int compt = 0;
	int pluspetitbat=bateau_plus_petit(joueur);

	for(int i=0;i<mat.nbl;i++){ 
		for(int j=0; j<mat.nbc;j++){
			if(mat.grille[i][j].c==AUCUNE){ //si la couleur de la case est aucune
				 compt++; //incrémente compt
			}
		}
	}
	if(compt == (mat.nbc*mat.nbl)){ //si aucun pion n'a été posé (1er tour)
		return aleatoire(mat); //choisir une case aléatoire
	}
	
	cell = detection_touche(mat); //si un bateau a été touché
	if(cell.x != -1 || cell.y != -1){
		return cell;
	}
	cell=est_autour(mat); //choisir un pion éloigné
	if(autorisation_case(mat, cell)){
		return cell;
	}
	if(pseudo_aleatoire_autorisation(mat, pluspetitbat)){ //choisir une case pseudo aléatoirement
		return pseudo_aleatoire(mat, pluspetitbat);
	}
	return aleatoire(mat); //choisir une case aléatoirement
}
