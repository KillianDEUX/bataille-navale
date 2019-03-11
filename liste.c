#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
typedef struct element{
	bateau_t bateau; 
	struct element * pred; 
	struct element * succ
}t_element;

typedef struct {
	t_element * drapeau;
	t_element * ec;
}t_liste;

void init_liste(liste* p){
	p->drapeau= malloc(sizeof(t_element));
	p->drapeau->pred= p->drapeau;
	p->drapeau->succ=p->drapeau;
	p->ec=p->drapeau;
}

int liste_vide(liste* p){
	return (p->drapeau->succ == p->drapeau);
}

int hors_liste(liste* p){
	return (p->ec==p->drapeau);
}

void en_tete(liste* p){
	if(!liste_vide(p)){
		p->ec=p->drapeau->succ;
	}
}

void en_queue(liste* p){
	if(!liste_vide(p)){
		p->ec=p->drapeau->pred;
	}
}

void suivant(liste* p){
	if(!hors_liste(p)){
		p->ec=p->ec->succ;
	}
}

void precedent(liste* p){
	if(!hors_liste(p)){
		p->ec=p->ec->pred;
	}		
}

void valeur_elt(liste* p, bateau_t * bat_v){
	if(!hors_liste(p)){
		*bat_v=p->ec->bateau;
	}
}

void modif_elt(liste* p, bateau_t * bat_v){
	if(!hors_liste(p)){	
		p->ec->bateau->taille= bat_v;
		(p->ec->pred)->succ=bat_v;
		(p->ec->succ)->pred=bat_v;		
	}
}

	
void oter_elt(liste* p){
	t_element * ancien;
	if(!hors_liste(p)){
		(p->ec->pred)->succ=p->ec->pred;
		(p->ec->succ)->pred=p->ec->succ;
		ancien=p->ec;
		p->ec=p->ec->pred;
		free(ancien);
	}
}

void ajout_droit(liste* p, bateau_t bat_v){
	t_element * nouveau;
	if(!hors_liste(p)){
		p->nouveau=malloc(sizeof(t_element));
		p->nouveau->pred=p->ec->bateau;
		p->nouveau->succ=p->ec->succ;
		p->ec->succ=bat_v;
		(p->nouveau->succ)->pred=bat_v;
	}
}


void ajout_gauche(liste* p, bateau_t bat_v){
	t_element * nouveau;
	if(!hors_liste(p)){
		p->nouveau=malloc(sizeof(t_element));
		p->nouveau->pred=p->ec->pred;
		p->nouveau->succ=p->ec->bateau;
		p->ec->pred=bat_v;
		(p->nouveau->pred)->succ=bat_v;
	}
}
