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
       
