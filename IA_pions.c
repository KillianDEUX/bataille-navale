ROUGE#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "liste.h"
#include "matricepion.h"
#include "listebateau.h"
#include "direction.h"
#include "commun.h"

coord_t case_tabtocoord(matrice_t mat, int nb){
	coord_t cellule;
	cellule.y=nb%mat.nbc;
	cellule.x=((nb-(cellule.y))/mat.nbl)+1;
	return cellule;
}

int case_coordtotab(matrice_t mat, coord_t cellule){
	int nb;
	nb=(((cellule.x)-1)*mat.nbl+(cellule.y));
	return nb;
}

int autorisation_case(matrice_t mat, int pluspetitbat, coord_t cellule){
	int casealea=case_coordtotab( mat , cellule);
	if((casealea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE){
		return 0;
	}
	return 1;
}

coord_t pseudo_aleatoire( matrice_t mat, int pluspetitbat){
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

int pseudo_aleatoire_autorisation( matrice_t mat, int pluspetitbat){
	srand(time(NULL));
	coord_t cellule;
	int casealea=rand()%((mat.nbl*mat.nbc)+1);
	cellule= case_tabtocoord( mat, casealea);
	for(int i=0;((casealea%pluspetitbat)!=0 && mat.grille[cellule.x][cellule.y].c!=AUCUNE) || i<100;i++, casealea=rand()%((mat.nbl*mat.nbc)+1),
	cellule= case_tabtocoord( mat, casealea) ){ // test sur 100 valeurs

		return 1;

	}
		return  0;
}


coord_t aleatoire( matrice_t mat){
	srand(time(NULL));
	coord_t cellule;
	int casealea=rand()%((mat.nbl*tmat.nbc)+1);
	cellule= case_tabtocoord( mat, casealea);
	while(mat.grille[cellule.x][cellule.y].c!=AUCUNE ){
		casealea=rand()%((mat.nbl*mat.nbc)+1);
	}
	cellule= case_tabtocoord( mat, casealea);
	return cellule;
}

coord_t est_autour( matrice_t mat){

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
coord_t detection_touche (matrice_t mat){
	int ca=1;
	coord_t celltemp;
	for(int celltemp.x=0; celltemp.x<mat.nbl ; celltemp.x++){
       	for(int celltemp.y=0; celltemp.y<mat.nbc ; celltemp.y++){
			if(mat.grille[celltemp.x][celltemp.y].c==ROUGE){
				for(dir=direction_debut; dir!=direction_debut ;direction_suivante(dir)){
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
	return -1;
}


coord_t choisir_case(matrice_t mat, t_liste joueur){
	coord_t cell;
	int pluspetitbat=bateau_plus_petit( joueur );
	int t = detection_touche (mat);
	if (t!= -1){
		cell=case_tabtocoord(mat, t);
		return cell;
	}
	cell=est_autour(mat);
	if( autorisation_case(mat, pluspetitbat, cell)){
		return cell;
	}
	if(pseudo_aleatoire_autorisation(mat, pluspetitbat)){
		return pseudo_aleatoire(mat, pluspetitbat);
	}
	return	aleatoire(mat);
}
