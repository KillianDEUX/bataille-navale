#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct case_s {
  int x;
  int y;
}case_t;


case_t case_tabtocoord(int taille, int nb){
  case_t cellule;
  cellule.y=nb%taille;
  cellule.x=((nb-(cellule.y))/taille)+1;
  return cellule;
}

int case_coordtotab(int taille, case_t cellule){
  int nb;
  nb=((cellule.x)*taille+(cellule.y));
  return nb;
}

case_t autorisation_case(int taille, int pluspetitbat){
  srand(time(NULL));
  case_t cellule;
  int casealea=rand()%((taille*taille)+1);
  while((casealea%pluspetitbat)!=0){
    casealea=rand()%((taille*taille)+1);
  }
  cellule= case_tabtocoord( taille, casealea);
  return cellule;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int est_autour( int taille, pion_t ptr[]){
// Verifier si il y a déjà des pions blancs à proximité
}

int detection_touche (int taille, case_t cell, pion_t ptr[]){
	int ca=0;
	for(int i=0; i<taille ; i++){
       		for(int j=0; j<taille ; j++){
			if((ptr[0]+i*taille+j).c==rouge){
				if( danslagrille(taille, cell.x, (cell.y+1))== 0){
                			if( (ptr[0]+(cell.x)*taille+(cell.y+1)).c== rouge){
                  				  return ptr[0]+(cell.x)*taille+(cell.y+1);
                 			 }
               			 }else if( danslagrille(taille, cell.x, (cell.y-1))== 0){
                   			 if( (ptr[0]+(cell.x)*taille+(cell.y-1)).c== rouge){
                  				  return ptr[0]+(cell.x)*taille+(cell.y-1);
                  			  }
             			 }else if ( danslagrille(taille, cell.x+1, cell.y)== 0){
                 			  if( (ptr[0]+((cell.x)+1)*taille+cell.y).c== rouge){
                   				  return ptr[0]+((cell.x)+1)*taille+cell.y;
                 			   }
            			 }else if ( danslagrille(taille, cell.x-1, cell.y)== 0){
                  			   if( (ptr[0]+((cell.x)-1)*taille+cell.y).c== rouge){
                    				 return ptr[0]+((cell.x)-1)*taille+cell.y;
					   }
              			}
				
				
				
				
                		if( danslagrille(taille, cell.x, (cell.y+1))== 0){
                			if( (ptr[0]+(cell.x)*taille+(cell.y+1)).c== aucune){
                  				  return ptr[0]+(cell.x)*taille+(cell.y+1);
                 			 }
               			 }else if( danslagrille(taille, cell.x, (cell.y-1))== 0){
                   			 if( (ptr[0]+(cell.x)*taille+(cell.y-1)).c== aucune){
                  				  return ptr[0]+(cell.x)*taille+(cell.y-1);
                  			  }
             			 }else if ( danslagrille(taille, cell.x+1, cell.y)== 0){
                 			  if( (ptr[0]+((cell.x)+1)*taille+cell.y).c== aucune){
                   				  return ptr[0]+((cell.x)+1)*taille+cell.y;
                 			   }
            			 }else if ( danslagrille(taille, cell.x-1, cell.y)== 0){
                  			   if( (ptr[0]+((cell.x)-1)*taille+cell.y).c== aucune){
                    				 return ptr[0]+((cell.x)-1)*taille+cell.y;
					   }
              			}
             		 }
          	}
	}
	return 0;
}

t_case choix_autour_touche (int taille, pion_t ptr[]){
 // Choisis une case adjacente au bateau touché non coulé dans sa continuité
}

case_t choisir_case(int taille){
  // Choix final de la case
}
