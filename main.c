#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_MAT_DEF 10

int demi_main( int nb_joueurs){

  int taille_mat= TAILLE_MAT_DEF;
   switch( nb_joueurs){
     case 5 :  t_liste joueur5;
     case 4 :  t_liste joueur4;
     case 3 :  t_liste joueur3;
     case 2 :  t_liste joueur2;
     case 1 :  t_liste joueur1; break;
     default : printf("Nombre de joueurs incorrect !");
   }
   if(nb_joueurs==1){
     t_liste ia;
     
     // TOURS DE JEU AVEC L'IA
   }else{
     // TOURS DE JEU EN RESEAU
   }
}
