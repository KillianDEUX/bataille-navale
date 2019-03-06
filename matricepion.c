// revoir si on change la matrice carrée en rectangulaire

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int creer_matrice_adv (int taille){
	
	case_t **ptr;

	ptr = malloc(taille * sizeof(*ptr)); 
	if(ptr == NULL){ 
		return 1;
	} 
	ptr[0]= malloc(taille * taille * sizeof(**ptr));
	if(ptr[0]== NULL){
		return 1;
	}
	for(int i=1; i<taille ; i++){
		ptr[i]= ptr[i-1]+taille;
	}
	return 0;
}



int init_matrice_adv (int taille, case_t ptr[]){

	for(int i=0; i<taille ; i++){
       	for(int j=0; j<taille ; j++){
           	(ptr[0]+i*taille+j).c= aucune;
        }
	}
	return 0;
}


int ajout_pion_matrice( int taille, case_t cell, case_t ptr[] ){

	if( etat_tir(taille, cell)==0){        				  // Si le tir tombe dans l'eau
		(ptr[0]+cell.x*taille+cell.y).c= blanc ;    	 // Placer un pion blanc sur la matrice
	}else if( etat_tir(taille, cell)==1){  			  // Si le tir touche une cible
		(ptr[0]+cell.x*taille+cell.y).c= rouge ;       // Placer un pion rouge sur la matrice
	}else if( etat_tir(taille, cell)==2){	 		// Si le tir coule une cible
		(ptr[0]+cell.x*taille+cell.y).c= rouge ; 	 // Placer un pion rouge sur la matrice
		eauautourcoule(taille, cell);       		 // Placer des pion blancs tout autour sur la matrice
	}else{
		return 1;
	}
	return 0;
}
	

	
void danslagrille(int taille, case_t cell ){
	
	if( cell.x >= taille || cell.y >= taille || cell.x < 1 || cell.y < 1 )
		return 0;
	return 1;
}
	
	
void eauautourcoule( int taille, case_t cell, case_t ptr[] ){
	// Lorsque le bateau est dirigé vers le nord
	case_t celltemp;
	celltemp.x=cell.x+1;
	celltemp.y=cell.y;
	if ( danslagrille(taille, celltemp)){
		if( (ptr[0]+celltemp.x*taille+(celltemp.y)).c== aucune){
			(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
		}else if ((ptr[0]+celltemp.x*taille+(celltemp.y)).c== rouge){
			while((danslagrille(taille, celltemp)) && ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
				}
				celltemp.y++;
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers le sud
	int celltemp.y=cell.y-1; 									// Changement 
	int celltemp.x=cell.x;
	if ( danslagrille(taille, celltemp)){
		if( (ptr[0]+celltemp.x*taille+celltemp.y).c== aucune){
			(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
		}else if ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge){
			while((danslagrille(taille, celltemp)) && ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge)){
				celltemp.x=cell.x+1;
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
				}
				celltemp.x=cell.x-1;
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
				}
				celltemp.y--;                   					// Changement 
			}
			celltemp.x=cell.x+1;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.x=cell.x-1;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.x=cell.x;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'est
	int celltemp.y=cell.y;                   				                        // Changement 			
	int celltemp.x=cell.x+1;                  					                // Changement 
	if ( danslagrille(taille, celltemp)){
		if( (ptr[0]+celltemp.x*taille+celltemp.y).c== aucune){
			(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
		}else if ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge){
			while((danslagrille(taille, celltemp)) && ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge)){
				celltemp.y=cell.y+1;							// Changement
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
				}
				celltemp.y=cell.y-1;							// Changement
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
				}
				celltemp.x++;							// Changement                   					
			}
			celltemp.y=cell.y+1;								// Changement
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.y=cell.y-1;								// Changement
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.y=cell.y;								// Changement
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
		}
	}
	// Lorsque le bateau est dirigé vers l'ouest
	int celltemp.y=cell.y;                   				                        		
	int celltemp.x=cell.x-1;                  					                // Changement 
	if ( danslagrille(taille, celltemp)){
		if( (ptr[0]+celltemp.x*taille+celltemp.y).c== aucune){
			(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
		}else if ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge){
			while((danslagrille(taille, celltemp)) && ((ptr[0]+celltemp.x*taille+celltemp.y).c== rouge)){
				celltemp.y=cell.y+1;							
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+(celltemp.y)).c= blanc;
				}
				celltemp.y=cell.y-1;							
				if(danslagrille(taille, celltemp)){
					(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
				}
				celltemp.x--;							// Changement                   					
			}
			celltemp.y=cell.y+1;								
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.y=cell.y-1;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
			celltemp.y=cell.y;
			if(danslagrille(taille, celltemp)){
				(ptr[0]+celltemp.x*taille+celltemp.y).c= blanc;
			}
		}
	}
}



void vider_matrice(int taille){
	init_matrice_adv (taille);
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_pion( int taille){
	for(int i=0; i<taille ; i++){
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










