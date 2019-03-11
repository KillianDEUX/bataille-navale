// revoir si on change la matrice carrée en rectangulaire

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct case_s {
	int x;
	int y;
	couleur_t c;
}case_t;

case_t **creer_matrice_adv (int taille){
	
	case_t **ptr;

	ptr = malloc(taille * sizeof(*ptr)); 
	if(ptr == NULL){ 
		printf("Code erreur : manque de mémoire");
	} 
	ptr[0]= malloc(taille * taille * sizeof(**ptr));
	if(ptr[0]== NULL){
		printf("Code erreur : manque de mémoire");
	}
	for(int i=1; i<taille ; i++){
		ptr[i]= ptr[i-1]+taille;
	}
	return ptr;
}

void detruire_matrice_adv( case_t **ptr){
	free(ptr[0]);
	free(ptr);
}


int init_matrice_adv(int taille, case_t** ptr){

	for(int i=0; i<taille ; i++){
       	for(int j=0; j<taille ; j++){
           	ptr[i][j].c= aucune;
        }
	}
	return 0;
}free(ptr);


	
int danslagrille(int taille, case_t cell ){
	
	if( cell.x >= taille || cell.y >= taille || cell.x < 1 || cell.y < 1 )
		return 0;
	return 1;
}
	
	
void eauautourcoule( int taille, case_t cell, case_t** ptr ){
	// Lorsque le bateau est dirigé vers le nord
	case_t celltemp;
	celltemp.x=cell.x+1;
	celltemp.y=cell.y;
	if ( danslagrille(taille, celltemp)){
		if( ptr[celltemp.x][celltemp.y].c== aucune){
			ptr[celltemp.x][celltemp.y].c= blanc;
		}else if (ptr[celltemp.x][celltemp.y].c== rouge){
			while((danslagrille(taille, celltemp)) && (ptr[celltemp.x][celltemp.y].c== rouge)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.y++;
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	celltemp.y=cell.y-1; 									// Changement 
	celltemp.x=cell.x;
	if ( danslagrille(taille, celltemp)){
		if( ptr[celltemp.x][celltemp.y].c== aucune){
			ptr[celltemp.x][celltemp.y].c= blanc;
		}else if (ptr[celltemp.x][celltemp.y].c== rouge){
			while((danslagrille(taille, celltemp)) && (ptr[celltemp.x][celltemp.y].c== rouge)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					(ptr[celltemp.x][celltemp.y]).c= blanc;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.y--;                   					// Changement 
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	celltemp.y=cell.y;                   				                        // Changement 			
	celltemp.x=cell.x+1;                 					                // Changement 
	if ( danslagrille(taille, celltemp)){
		if( ptr[celltemp.x][celltemp.y].c== aucune){
			ptr[celltemp.x][celltemp.y].c= blanc;
		}else if (ptr[celltemp.x][celltemp.y].c== rouge){
			while((danslagrille(taille, celltemp)) && (ptr[celltemp.x][celltemp.y].c== rouge)){
				celltemp.y=cell.y+1;							// Changement
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.y=cell.y-1;							// Changement
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.x++;							// Changement                   					
			}
			celltemp.y=cell.y+1;								// Changement
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.y=cell.y-1;								// Changement
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.y=cell.y;								// Changement
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	celltemp.y=cell.y;                   				                        		
	celltemp.x=cell.x-1;                  					                // Changement 
	if ( danslagrille(taille, celltemp)){
		if( ptr[celltemp.x][celltemp.y].c== aucune){
			ptr[celltemp.x][celltemp.y].c= blanc;
		}else if (ptr[celltemp.x][celltemp.y].c== rouge){
			while((danslagrille(taille, celltemp)) && (ptr[celltemp.x][celltemp.y].c== rouge)){
				celltemp.y=cell.y+1;							
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.y=cell.y-1;							
				if(danslagrille(taille, celltemp)){
					ptr[celltemp.x][celltemp.y].c= blanc;
				}
				celltemp.x--;							// Changement                   					
			}
			celltemp.y=cell.y+1;								
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.y=cell.y-1;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
			celltemp.y=cell.y;
			if(danslagrille(taille, celltemp)){
				ptr[celltemp.x][celltemp.y].c= blanc;
			}
		}
	}
}



int ajout_pion_matrice( int taille, case_t cell, case_t **ptr, bateau_t * actuel){

	if( etat_tir(taille, cell, actuel)==0){        				  // Si le tir tombe dans l'eau
		(ptr[cell.x][cell.y]).c= blanc ;    	 // Placer un pion blanc sur la matrice
	}else if( etat_tir(taille, cell, actuel)==1){  			  // Si le tir touche une cible
		(ptr[cell.x][cell.y]).c= rouge ;       // Placer un pion rouge sur la matrice
	}else if( etat_tir(taille, cell, actuel)==2){	 		// Si le tir coule une cible
		(ptr[cell.x][cell.y]).c= rouge ; 	 // Placer un pion rouge sur la matrice
		eauautourcoule(taille, cell, ptr);       		 // Placer des pion blancs tout autour sur la matrice
	}else{
		return 1;
	}
	return 0;
}


int vider_matrice(int taille, case_t **ptr){
	int i=init_matrice_adv(taille, ptr);
	return i;
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_pion( int taille, case_t **ptr){
	for(int i=0; i<taille ; i++){
       		for(int j=0; j<taille ; j++){
           		if(ptr[i][j].c == aucune){
				printf(". ");
			}else if(ptr[i][j].c == blanc){
				printf("0 ");
			}else{
				printf("X ");
			}
		}
		printf("\n");
	}
}











