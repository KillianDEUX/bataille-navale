#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct case_s {
  int x;
  int y;
}case_t;


case_t case_tabtocoord(int taille, int nb){
  case_t cellule;
  cellule.x=nb%taille;
  cellule.y=((nb-(cellule.x))/taille)+1;
  return cellule;
}

int case_coordtotab(int taille, case_t cellule){
  int nb;
  nb=((cellule.y)*taille+(cellule.x));
  return nb;
}

case_t autorisation_case(int taille, int pluspetitbat){
  srand(time(NULL));
  case_t cellule;
  int casealea=rand()%((taille*taille)+1);
  while((casealea%pluspetitbat)!=0){
    casealea=rand()%((taille*taille)+1);
  }
  cellule= case_tabtocoord( taille, casealea);
  return cellule;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int est_autour( int taille, pion ptr[]){
// Verifier si il y a déjà des pions blancs à proximité
}

int detection_touche (int taille, pion ptr[]){
 // Verifie si il y a déjà un bateau touché non coulé
}

t_case choix_autour_touche (int taille, pion ptr[]){
 // Choisis une case adjacente au bateau touché non coulé dans sa continuité
}

case_t choisir_case(int taille){
  // Choix final de la case
}
