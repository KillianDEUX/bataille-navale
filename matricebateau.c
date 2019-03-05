#include <stdio.h>
#include <stdlib.h
#include "liste.h"

typedef struct bateau {
		int b;	
} bateau_t;

int creer_matrice_bateau (int taille){
	
	bateau_t **bat;

	bat = malloc(taille * sizeof(*bat)); 
	if(ptr == NULL){ 
		return 1;
	} 
	 bat[0]= malloc(taille * taille * sizeof(**bat));
	     if(bat[0]== NULL){
		return 1;
	     }

	}
	for(int i=1; i<taille ; i++){
		bat[i]== bat[i-1]+taille;
	}

}


int init_matrice_bat (int taille, bateau_t bat[]){

	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		(bat[0]+i*taille+j).p= 0;
		}
	return 0;
}

void vider_matrice(int taille){
	init_matrice_bat (taille);
}


void choixbateau(int taille){
       char fich[20] = 'bateau.txt';
       FILE * fic1;
       int nbbat=0;
       int nbmaxbat = (0,06 * (M*N)) - (0,3 * N) +2;
       fic1= fopen(fich, "w");
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bâteau voulez-vous avoir ?(différent de 0 et inférieur à la moitié du nombre de case du terrain de jeu) : ");
              scanf("%i", &nbbat);
       }
       fprintf(fic1,"%i", nbbat);
       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     fprintf(fic1, "%i", t);
              }
       }
}
       





// Voir avec la SDL. Ici version terminal
void afficher_matrice_bat( int taille){
	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		if((bat[0]+i*taille+j).p == 0){
				printf(". ");
			}
			else{
				printf(" [] ");
			}
		}
		printf("\n");
	}
}

void ( int taille, int abs, int ord, bateau_t bat[] ){
	// Lorsque le bateau est dirigé vers le nord
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
	}
}

void placerbateau(bateau_t bat[], int taille, int n_bateau, char dir, case_t emp){
	FILE *fic;
	int entier, nb_bateau;
	int nb_case_bateau = 0; 
	int pos;
	fic = fopen("bateau.txt", "r");
	for(int i=; !feof(fic); i++){
		fscanf(fic, "%i", &entier);
		if(i == 0){
			nb_bateau = entier;
		}
		else if(i == n_bateau){
			 nb_case_bateau = entier;
		}
		if(nb_bateau < n_bateau){
			printf("Ce bateau n'existe pas");
			exit 0;	
		}
	}
	pos = case_coordtotab(taille, emp);
	
	
	
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
