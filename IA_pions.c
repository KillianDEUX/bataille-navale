#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "liste.h"
#include "matricepion.h"
#include "matricebateau.h"
#include "direction.h"

case_t case_tabtocoord(int taille, int nb){
	case_t cellule;
	cellule.y=nb%taille;
	cellule.x=((nb-(cellule.y))/taille)+1;
	return cellule;
}

int case_coordtotab(int taille, case_t cellule){
	int nb;
	nb=(((cellule.x)-1)*taille+(cellule.y));
	return nb;
}

int autorisation_case(int taille, int pluspetitbat, case_t cellule){
	int casealea=case_coordtotab( taille, cellule);
	if((casealea%pluspetitbat)!=0 && cellule.c!=aucune){
		return 0;
	}
	return 1;
}

case_t pseudo_aleatoire( int taille, int pluspetitbat){
	srand(time(NULL));
	case_t cellule;
	int casealea=rand()%((taille*taille)+1);
	cellule= case_tabtocoord( taille, casealea);
	while((casealea%pluspetitbat)!=0 && cellule.c!=aucune){
		casealea=rand()%((taille*taille)+1);
	}
	cellule= case_tabtocoord( taille, casealea);
	return cellule;
}

int pseudo_aleatoire_autorisation( int taille, int pluspetitbat){
	srand(time(NULL));
	case_t cellule;
	int casealea=rand()%((taille*taille)+1);
	cellule= case_tabtocoord( taille, casealea);
	for(int i=0;((casealea%pluspetitbat)!=0 && cellule.c!=aucune) || i<100;i++, casealea=rand()%((taille*taille)+1),
	cellule= case_tabtocoord( taille, casealea) ){ // test sur 100 valeurs

		return 1;
	
	}
		return  0;
}


case_t aleatoire( int taille){
	srand(time(NULL));
	case_t cellule;
	int casealea=rand()%((taille*taille)+1);
	cellule= case_tabtocoord( taille, casealea);
	while(cellule.c!=aucune ){
		casealea=rand()%((taille*taille)+1);
	}
	cellule= case_tabtocoord( taille, casealea);
	return cellule;
}

case_t est_autour( int taille,case_t  **ptr){
	
	int compt=0;
	int comptmax=0;
	int pion;
	case_t cell;
	for (int i=0;i<taille;i++){
		for(int j=0; j<taille;j++){
			if(ptr[i][j].c==aucune){
				 compt++;
				 if(compt>comptmax){
				 	comptmax=compt;
				 	pion=i*taille+j;
				}
			}else{
				compt=0;
			}
		}
	}
	pion=pion-(comptmax/2);
	cell= case_tabtocoord(taille, pion);
	return cell;
}


/* vérifie si un bateau est touché quelque part, et essaye de viser une case qui est à coté */
case_t detection_touche (int taille, case_t **ptr){
	int ca=1;
	case_t celltemp;
	for(int celltemp.x=0; celltemp.x<taille ; celltemp.x++){
       	for(int celltemp.y=0; celltemp.y<taille ; celltemp.y++){
			if(ptr[celltemp.x][celltemp.y].c==rouge){
				for(dir=direction_debut; dir!=direction_debut ;direction_suivante(dir)){
					celltemp=direction_avancer( dir,celltemp, ca );
					while(danslagrille(taille,celltemp) && ptr[celltemp.x][celltemp.y].c==rouge){
                  		ca++;
                  		celltemp=direction_avancer( dir,celltemp, ca );
               		}
					if(danslagrille(taille, celltemp) && ptr[celltemp.x][celltemp.y].c==aucune){
						return celltemp;
					}
				}
			}
        }
	}
	return -1;
}


case_t choisir_case(int taille, case_t **ptr, t_liste joueur){
	case_t cell;
	int pluspetitbat=bateau_plus_petit( joueur );
	int t = detection_touche ( taille, ptr);
	if (t!= -1){
		cell=case_tabtocoord(taille, t);
		return cell;
	}
	cell=est_autour(taille, ptr);
	if( autorisation_case(taille, pluspetitbat, cell)){
		return cell;
	}
	if(pseudo_aleatoire_autorisation(taille, pluspetitbat)){
		return pseudo_aleatoire(taille, pluspetitbat);
	}
	return	aleatoire(taille);
}
