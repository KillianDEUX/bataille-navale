#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

typedef enum type_bat {aucun, mine ,torpilleur, sousmarin,  croiseur, porte-avion}type_t;
typedef enum dir_bat {aucun, vertical, horizontal}dir_t;
typedef enum etat_bat {flotte, coule}etat_t;

typedef struct bateau {
	type_t type;
	int coordx;
	int coordy;
	int taille;
	dir_t dir;
	etat_t etat;
}bateau_t;


void choixbateau(int taille){
       init_liste();
       int nbbat=0;
       bateau_t nouveau;
       int nbmaxbat = (0,06 * (taille*taille)) - (0,3 * taille) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bâteau voulez-vous avoir ?(différent de 0 et inférieur à la moitié du nombre de case du terrain de jeu) : ");
              scanf("%i", &nbbat);
       }
       
       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     en_tete();
                     nouveau->taille = t;
                     nouveau->coordx = -1;
                     nouveau->coordy = -1;
                     nouveau->dir = aucun;
                     nouveau->type = aucun;
                     nouveau->etat = flotte;
                     ajout_droit(nouveau);
              }
       }
}
       
position_bateau_vertical(bateau_t bateau){
	return (bateau->coordy + bateau->taille);
}
       
position_bateau_horizontal(bateau_t bateau){
	return (bateau->coordx + bateau->taille); 
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_bateau(int taille){
	int coordx, coordy;
	bateau_t * actuel;
	for(int i=0; i<taille ; i++){
       	for(int j=0; j<taille ; j++){
       		entete();
       		while(!hors_liste()){
       			valeur_elt(*actuel);
       			if(i==actuel->coordx && j==actuel->coordy){
       				if(actuel->dir == vertical){
       					position_bateau_vertical(actuel);
       					for(int k=j; k< (position_bateau_vertical(actuel)); k++){
       						printf("[.]");
       					}
       				}
       				if(actuel->dir == horizontal){
       					position_bateau_horizontal(actuel);
       					for(int k=j; k< (position_bateau_horizontal(actuel)); k++){
       						printf("[.]");
       					}
       				}
       			}
       			else{
       				printf("[]");
       			}
       			suivant();
       		}
       	}
    }
}


void ( int taille, int abs, int ord, bateau_t bat[] ){
	
	
	
	/*// Lorsque le bateau est dirigé vers le nord
	int ordtemp=ord+1;
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (bat[0]+abstemp*taille+(ordtemp)).b== 1){
			return 1;				
		}else{
			abstemp=abs+1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				if (bat[0]+abstemp*taille+(ordtemp)).b= 1){
					return 1;
				}
			}
			abstemp=abs-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				if (bat[0]+abstemp*taille+(ordtemp)).b= 1){
					return 1;
				}
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	int ordtemp=ord-1; 									// Changement 
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr[0]+abstemp*taille+ordtemp).c== aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c== rouge){
				abstemp=abs+1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp=abs-1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+ordtemp).c= blanc;
				}
				ordtemp--;                   					// Changement 
			}
			abstemp=abs+1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			abstemp=abs-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			abstemp=abs;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	int ordtemp=ord;                   				                        // Changement 			
	int abstemp=abs+1;                  					                // Changement 
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr[0]+abstemp*taille+ordtemp).c== aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c== rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c== rouge)){
				ordtemp=ord+1;							// Changement
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp=ord-1;							// Changement
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp++;							// Changement                   					
			}
			ordtemp=ord+1;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord-1;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	int ordtemp=ord;                   				                        		
	int abstemp=abs-1;                  					                // Changement 
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr[0]+abstemp*taille+ordtemp).c== aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c== rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c== rouge)){
				ordtemp=ord+1;							
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp=ord-1;							
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp--;							// Changement                   					
			}
			ordtemp=ord+1;								
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}*/
}

void placerbateau(bateau_t bat[], int taille, int n_bateau, char dir, case_t emp){

}
	
	
	
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
