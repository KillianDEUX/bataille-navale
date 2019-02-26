#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

typedef enum couleur { aucune, blanche, rouge }

typedef struct pion {
		couleur c;
		int x;
		char y;
} pion_t;

void init_matrice_adv (int taille){

pion **ptr;
ptr = malloc(taille * sizeof(*ptr)); 
if(ptr == NULL){ 
	return 1;
} 
for(i=0 ; i < taille ; i++){
     ptr[i] = malloc(taille * sizeof(**ptr) );
     if(ptr[i] == NULL){
	return 1;
     }
}

    for(int i=0; i<taille ; i++)
        for(int j=0; j<taille ; j++)
            (ptr+i*taille+j).c= "aucune" ;
    	    (ptr+i*taille+j).x='a'+i;
	    (ptr+i*taille+j).y=j;
}

void ajout_pion_matrice( int taille, int abs, char ord ){

	if( etat_tir(taille, abs, ord)==0){
		 (ptr+abs*taille+ord).c= "aucune" ;
		








void init_matrice_joueur (int mat_j [N][N]){

    for(int i=0; i<N ; i++)
        for(int j=0; j<N ; j++)
	    mat_j [i][j]= 0;
}




int **ptr;
ptr = malloc(taille * sizeof(*ptr)); 
if(ptr == NULL){ 
	return 1;
} 
for(i=0 ; i < taille ; i++){
     ptr[i] = malloc(taille * sizeof(**ptr) );
     if(ptr[i] == NULL){
	return 1;
     }
}



















