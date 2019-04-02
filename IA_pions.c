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
	cellule.y=nb%mat.nbc;
	cellule.x=((nb-(cellule.y))/mat.nbl)+1;
	return cellule;
}

// transforme des coordonnées x,y en numéro de case
int case_coordtotab(matrice_pion_t mat, coord_t cellule){
	int nb;
	nb=(((cellule.x)-1)*mat.nbl+(cellule.y));
	return nb;
}

// Verifie si l'IA peut placer un pion à l'endoit cellule
int autorisation_case(matrice_pion_t mat, int pluspetitbat, coord_t cellule){
	int casealea=case_coordtotab( mat , cellule);
	if((casealea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE){
		return 0;
	}
	return 1;
}

// Place un pion de manière pseudo aleatoire
coord_t pseudo_aleatoire( matrice_pion_t mat, int pluspetitbat){
	srand(time(NULL));
	coord_t cellule;
	int casealea=rand()%((mat.nbl*mat.nbc)+1);
	cellule= case_tabtocoord( mat, casealea);
	while((casealea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE){
		casealea=rand()%((mat.nbl*mat.nbc)+1);
	}
	cellule= case_tabtocoord( mat , casealea);
	return cellule;
}

// Verifie si l'IA peut placer un pion à l'endoit cellule
int pseudo_aleatoire_autorisation( matrice_pion_t mat, int pluspetitbat){
	int i;
	srand(time(NULL));
	coord_t cellule;
	int casealea=rand()%((mat.nbl*mat.nbc)+1);
	cellule= case_tabtocoord( mat, casealea);
	for(i=0;((casealea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE) || i<100;i++){ // test sur 100 valeurs
 		casealea=rand()%((mat.nbl*mat.nbc)+1);
		cellule= case_tabtocoord( mat, casealea);
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
	int casealea=rand()%((mat.nbl*mat.nbc)+1);
	cellule= case_tabtocoord( mat, casealea);
	while(mat.grille[cellule.x][cellule.y].c!=AUCUNE ){
		casealea=rand()%((mat.nbl*mat.nbc)+1);
	}
	cellule= case_tabtocoord( mat, casealea);
	return cellule;
}

// Choisis une case éloignés de toutes les autres
coord_t est_autour( matrice_pion_t mat){

	int compt=0;
	int comptmax=0;
	int pion;
	coord_t cell;
	for (int i=0;i<mat.nbl;i++){
		for(int j=0; j<mat.nbc;j++){
			if(mat.grille[i][j].c==AUCUNE){
				 compt++;
				 if(compt>comptmax){
				 	comptmax=compt;
				 	pion=i*mat.nbl+j;
				}
			}else{
				compt=0;
			}
		}
	}
	pion=pion-(comptmax/2);
	cell= case_tabtocoord(mat, pion);
	return cell;
}


/* vérifie si un bateau est touché quelque part, et essaye de viser une case qui est à coté */
coord_t detection_touche (matrice_pion_t mat){
	int ca=1;
	direction_t dir;
	coord_t celltemp;
	for( celltemp.x=0; celltemp.x<mat.nbl ; celltemp.x++){
       	for(celltemp.y=0; celltemp.y<mat.nbc ; celltemp.y++){
			if(mat.grille[celltemp.x][celltemp.y].c==ROUGE){
				for(dir=direction_debut(); dir!=OUEST ;direction_suivante(dir)){
					celltemp=direction_avancer( dir, celltemp, ca );
					while(danslagrille(mat,celltemp) && mat.grille[celltemp.x][celltemp.y].c==ROUGE){
                  		ca++;
                  		celltemp=direction_avancer( dir, celltemp, ca );
               		}
					if(danslagrille(mat, celltemp) && mat.grille[celltemp.x][celltemp.y].c==AUCUNE){
						return celltemp;
					}
				}
			}
    }
	}
	return celltemp;
}

// Choisis une case de la façon la plus adapté
coord_t choisir_case(matrice_pion_t mat, t_liste joueur){
	coord_t cell;
	int pluspetitbat=bateau_plus_petit( joueur );
	cell = detection_touche (mat);
	cell=est_autour(mat);
	if( autorisation_case(mat, pluspetitbat, cell)){
		return cell;
	}
	if(pseudo_aleatoire_autorisation(mat, pluspetitbat)){
		return pseudo_aleatoire(mat, pluspetitbat);
	}
	return	aleatoire(mat);
}
