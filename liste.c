#include<stdio.h>
#include<stdlib.h>
typedef struct element{bateau_t bateau; 
	struct element * pred; 
	struct element * succ
	}t_element;
t_element * drapeau;
t_element * ec;

void init_liste(){
	drapeau= malloc(sizeof(t_element));
	drapeau->pred= drapeau;
	drapeau->succ=drapeau;
	ec=drapeau;
}

int liste_vide(){
	return (drapeau->succ == drapeau);
}

int hors_liste(){
	return (ec==drapeau);
}

void en_tete(){
	if(!liste_vide()){
		ec=drapeau->succ;
	}
}

void en_queue(){
	if(!liste_vide()){
		ec=drapeau->pred;
	}
}

void suivant(){
	if(!hors_liste()){
		ec=ec->succ;
	}
}

void precedent(){
	if(!hors_liste()){
		ec=ec->pred;
	}		
}

void valeur_elt(int * v){
	if(!hors_liste()){
		*v=ec->bateau;
	}
}

void modif_elt(int * v){
	if(!hors_liste()){	
		ec->bateau->taille= v;
		(ec->pred)->succ=v;
		(ec->succ)->pred=v;		
	}
}

	
void oter_elt(){
	t_element * ancien;
	if(!hors_liste()){
		(ec->pred)->succ=ec->pred;
		(ec->succ)->pred=ec->succ;
		ancien=ec;
		ec=ec->pred;
		free(ancien);
	}
}

void ajout_droit(int v){
	t_element * nouveau;
	if(!hors_liste()){
		nouveau=malloc(sizeof(t_element));
		nouveau->pred=ec->bateau;
		nouveau->succ=ec->succ;
		ec->succ=v;
		(nouveau->succ)->pred=v;
	}
}


void ajout_gauche(int v){
	t_element * nouveau;
	if(!hors_liste()){
		nouveau=malloc(sizeof(t_element));
		nouveau->pred=ec->pred;
		nouveau->succ=ec->bateau;
		ec->pred=v;
		(nouveau->pred)->succ=v;
	}
}
