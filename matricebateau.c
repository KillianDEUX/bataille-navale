#include <stdio.h>
#include <stdlib.h
#include "liste.h"


void choixbateau(int N, int M){
       init_liste();
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
           		(bat[0]+i*taille+j).c= aucune;
	}
	return 0;
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

void placerbateau(int mat[N][M], int N, int M, int n_bateau, char dir, int x, int y){
              
              
