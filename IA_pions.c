#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct case_s {
	int x;
	int y;
	couleur_t c;
}case_t;


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
	int casealea=case_coordtotab( taille, cellule)
	if((casealea%pluspetitbat)!=0 && cellule.c!=aucune){
		return 0
	}
	return 1;
}

case_t pseudo_aleatoire( int taille, int pluspetitbat){
	srand(time(NULL));
	case_t cellule;
	int casealea=rand()%((taille*taille)+1);
	while((casealea%pluspetitbat)!=0 && cellule.c!=aucune){
		casealea=rand()%((taille*taille)+1);
	}
	cellule= case_tabtocoord( taille, casealea);
	return cellule;
}

int pseudo_aleatoire_autorisation( int taille, int pluspetitbat){
	srand(time(NULL));
	int casealea=rand()%((taille*taille)+1);
	for(int i=0;((casealea%pluspetitbat)!=0 && cellule.c!=aucune) || i<100;i++){ // test sur 100 valeurs
		return 1;
	}
		return  0;
}


case_t aleatoire( int taille){
	srand(time(NULL));
	case_t cellule;
	int casealea=rand()%((taille*taille)+1);
	while(casealea.c!=aucune && ){
		casealea=rand()%((taille*taille)+1);
	}
	cellule= case_tabtocoord( taille, casealea);
	return cellule;
}

case_t est_autour( int taille, case_t ptr[]){
	
	int compt=0;
	int comptmax=0;
	int pion;
	case_t cell;
	for (int i=0;i<taille;i++){
		for(int j=0; j<taille;j++){
			if((ptr[0]+i*taille+j).c==aucun){
				 compt++
				 if(compt>comptmax){
				 	comptmax=compt;
				 	pion=i*taille+j
				}
			}else{
				compt=0;
			}
		}
	}
	pion=pion-(comptman/2);
	cell= case_tabtocoord(taille, pion);
	return cell;
}

int detection_touche (int taille, case_t ptr[]){
	int ca=1;
	for(int i=0; i<taille ; i++){
       	for(int j=0; j<taille ; j++){
			if((ptr[0]+i*taille+j).c==rouge){
				if( danslagrille(taille, i, (j+ca))== 0){
                	while( (ptr[0]+(i)*taille+(j+ca)).c== rouge){
                  		ca++;
               		}
					if( danslagrille(taille, i, (j+ca))== 0 && (ptr[0]+(i)*taille+(j+ca)).c== aucune){
						return (i)*taille+(j+ca);
					}
               	}else if( danslagrille(taille, i, (j-ca))== 0){
                   	while( (ptr[0]+(i)*taille+(j-ca)).c== rouge){
                  		ca++;
                 	}
					if( danslagrille(taille, i, (j-ca))== 0 && (ptr[0]+(i)*taille+(j-ca)).c== aucune){
						return (i)*taille+(j-ca);
					}
             	}else if ( danslagrille(taille, i+ca, j)== 0){
                 	while( (ptr[0]+(i+ca)*taille+(j)).c== rouge){
                  		ca++;
                 	}
					if( danslagrille(taille, i+ca, (j))== 0 && (ptr[0]+(i+ca)*taille+(j)).c== aucune){
						return (i+ca)*taille+(j);
					}
            	}else if ( danslagrille(taille, i-ca, j)== 0){
                  	while( (ptr[0]+(i-ca)*taille+(j)).c== rouge){
                  		ca++;
                 	}
					if( danslagrille(taille, i-ca, (j))== 0 && (ptr[0]+(i-ca)*taille+(j)).c== aucune){
						return (i-ca)*taille+(j);
					}
              	}
				if( danslagrille(taille, i, (j+1))== 0){
                	if( (ptr[0]+(i)*taille+(j+1)).c== aucune){
                  		return (i)*taille+(j+1);
                 	}
               	}else if( danslagrille(taille, i, (j-1))== 0){
                   	if( (ptr[0]+(i)*taille+(j-1)).c== aucune){
                  		return (i)*taille+(j-1);
                  	}
             	}else if ( danslagrille(taille, i+1, j)== 0){
                 	if( (ptr[0]+((i)+1)*taille+j).c== aucune){
                   		return (i+1)*taille+j;
                 	}
            	}else if ( danslagrille(taille, i-1, j)== 0){
                  	if( (ptr[0]+((i)-1)*taille+j).c== aucune){
                    	return (i-1)*taille+j;
					}
              	}
            }
        }
	}
	return -1;
}


case_t choisir_case(int taille, int pluspetitbat, case_t ptr[]){
	case_t cell;
	int t = detection_touche ( taille, ptr);
	if (t!= -1){
		cell=case_tabtocoord(taille, t)
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
