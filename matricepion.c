// revoir si on change la matrice carrée en rectangulaire

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef enum couleur { aucune, blanc, rouge } couleur_t;


typedef struct {
		couleur_t c;	
} pion_t;

typedef struct bateau {
		int b;	
} bateau_t;


int creer_matrice_adv (int taille){
	
	pion_t **ptr;

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
		ptr[i]= ptr[i-1]+taille;
	}

}

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
int init_matrice_adv (int taille, pion_t ptr[]){

	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		(ptr[0]+i*taille+j).c= aucune;
	}
	return 0;
}


int ajout_pion_matrice( int taille, int abs, int ord, pion_t ptr[] ){

	if( etat_tir(taille, abs, ord)==0){            // Si le tir tombe dans l'eau
		 (ptr[0]+abs*taille+ord).c= blanc ;     // Placer un pion blanc sur la matrice
	}else if( etat_tir(taille, abs, ord)==1){      // Si le tir touche une cible
		(ptr[0]+abs*taille+ord).c= rouge ;      // Placer un pion rouge sur la matrice
	}else if( etat_tir(taille, abs, ord)==2){					       // Si le tir coule une cible
		(ptr[0]+abs*taille+ord).c= rouge ;      // Placer un pion rouge sur la matrice
		eauautourcoule(taille, abs, ord);      // Placer des pion blancs tout autour sur la matrice
	}else{
		return 1;
	}
	return 0;
}
	

int init_matrice_bat (int taille, bateau_t bat[]){

	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		(bat[0]+i*taille+j).c= aucune;
	}
	return 0;
}

	
void danslagrille(int taille, int abs, int ord ){
	
	if( abs >= taille || ord >= taille || abs < 1 ||ord < 1 )
		return 1;
	return 0;
}
	
	
void eauautourcoule( int taille, int abs, int ord, pion_t ptr[] ){
	// Lorsque le bateau est dirigé vers le nord
	int ordtemp=ord+1;
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr[0]+abstemp*taille+(ordtemp)).c= aucune){
			(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
		}else if ((ptr[0]+abstemp*taille+(ordtemp)).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c= rouge)){
				abstemp=abs+1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
				}
				abstemp=abs-1;
				if(danslagrille(taille, abstemp, ordtemp)== 0){
					(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
				}
				ordtemp++;
			}
			abstemp=abs+1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
			}
			abstemp=abs-1;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
			}
			abstemp=abs;
			if(danslagrille(taille, abstemp, ordtemp)== 0){
				(ptr[0]+abstemp*taille+(ordtemp)).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	int ordtemp=ord-1; 									// Changement 
	int abstemp=abs;
	if ( danslagrille(taille, abstemp, ordtemp)== 0){
		if( (ptr[0]+abstemp*taille+ordtemp).c= aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c= rouge)){
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
		if( (ptr[0]+abstemp*taille+ordtemp).c= aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c= rouge)){
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
		if( (ptr[0]+abstemp*taille+ordtemp).c= aucune){
			(ptr[0]+abstemp*taille+ordtemp).c= blanc;
		}else if ((ptr[0]+abstemp*taille+ordtemp).c= rouge){
			while((danslagrille(taille, abstemp, ordtemp)== 0) && ((ptr[0]+abstemp*taille+ordtemp).c= rouge)){
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
	
void vider_matrice(int taille){
	init_matrice_adv (taille);
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_pion( int taille){
	for(int i=0; i<taille ; i++)
       		for(int j=0; j<taille ; j++){
           		if((ptr[0]+i*taille+j).c == aucune){
				printf(". ");
			}else if((ptr[0]+i*taille+j).c == blanc){
				printf("0 ");
			}else{
				printf("X ");
			}
		}
		printf("\n");
	}
}










