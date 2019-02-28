#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct pion {
		couleur_t c;	
} pion_t;

int creer_matrice_adv (int taille){
	
	pion **ptr;

	ptr = malloc(taille * sizeof(*ptr)); 
	if(ptr == NULL){ 
		return 1;
	} 
	 ptr[0]= malloc(taille * taille * sizeof(**ptr));
	     if(ptr[0]== NULL){
		return 1;
	     }

	}
	for(int i=1; i<taille ; i++){
		ptr[i]== ptr[i-1]+taille;
	}

}
void init_matrice_adv (int taille){

	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		(ptr[0]+i*taille+j).c= aucune;
	}
}

// Remplacer tous les ptr par ptr[0] 

void ajout_pion_matrice( int taille, int abs, int ord ){

	if( etat_tir(taille, abs, ord)==0){            // Si le tir tombe dans l'eau
		 (ptr+abs*taille+ord).c= blanc ;     // Placer un pion blanc sur la matrice
	}else if( etat_tir(taille, abs, ord)==1){      // Si le tir touche une cible
		(ptr+abs*taille+ord).c= rouge ;      // Placer un pion rouge sur la matrice
	}else{					       // Si le tir coule une cible
		(ptr+abs*taille+ord).c= rouge ;      // Placer un pion rouge sur la matrice
		eauautourcoule(taille, abs, ord);      // Placer des pion blancs tout autour sur la matrice
	}
	
void danslagrille(int taille, int abs, int ord ){
	
	if( abs >= taille || ord >= taille || abs < 1 ||ord < 1 )
		return 1;
	return 0;
}
	
	
void eauautourcoule( int taille, int abs, int ord ){
	// Lorsque le bateau est dirigé vers le nord
	int ordtemp=ord+1;
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr+abstemp*taille+(ordtemp)).c= aucune){
			(ptr+abstemp*taille+(ordtemp)).c= blanc;
		}else if ((ptr+abstemp*taille+(ordtemp)).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr+abstemp*taille+ordtemp).c= rouge)){
				abstemp=abs+1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+(ordtemp)).c= blanc;
				}
				abstemp=abs-1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp++;
			}
			abstemp=abs+1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+(ordtemp)).c= blanc;
			}
			abstemp=abs-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+(ordtemp)).c= blanc;
			}
			abstemp=abs;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+(ordtemp)).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	int ordtemp=ord-1; 									// Changement 
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr+abstemp*taille+ordtemp).c= aucune){
			(ptr+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr+abstemp*taille+ordtemp).c= rouge)){
				abstemp=abs+1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp=abs-1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+ordtemp).c= blanc;
				}
				ordtemp--;                   					// Changement 
			}
			abstemp=abs+1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			abstemp=abs-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			abstemp=abs;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	int ordtemp=ord;                   				                        // Changement 			
	int abstemp=abs+1;                  					                // Changement 
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr+abstemp*taille+ordtemp).c= aucune){
			(ptr+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr+abstemp*taille+ordtemp).c= rouge)){
				ordtemp=ord+1;							// Changement
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp=ord-1;							// Changement
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp++;							// Changement                   					
			}
			ordtemp=ord+1;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord-1;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord;								// Changement
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	int ordtemp=ord;                   				                        		
	int abstemp=abs-1;                  					                // Changement 
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr+abstemp*taille+ordtemp).c= aucune){
			(ptr+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr+abstemp*taille+ordtemp).c= rouge)){
				ordtemp=ord+1;							
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp=ord-1;							
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr+abstemp*taille+ordtemp).c= blanc;
				}
				abstemp--;							// Changement                   					
			}
			ordtemp=ord+1;								
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
			ordtemp=ord;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr+abstemp*taille+ordtemp).c= blanc;
			}
		}
	}
}














