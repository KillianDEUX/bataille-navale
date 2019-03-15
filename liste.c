#include<stdio.h>
#include<stdlib.h>

#include "liste.h"


void init_liste(t_liste* p){
	p->drapeau= malloc(sizeof(t_element));
	p->drapeau->pred= p->drapeau;
	p->drapeau->succ=p->drapeau;
	p->ec=p->drapeau;
}

int liste_vide(t_liste* p){
	return (p->drapeau->succ == p->drapeau);
}

int hors_liste(t_liste* p){
	return (p->ec==p->drapeau);
}

void en_tete(t_liste* p){
	if(!liste_vide(p)){
		p->ec=p->drapeau->succ;
	}
}

void en_queue(t_liste* p){
	if(!liste_vide(p)){
		p->ec=p->drapeau->pred;
	}
}

void suivant(t_liste* p){
	if(!hors_liste(p)){
		p->ec=p->ec->succ;
	}
}

void precedent(t_liste* p){
	if(!hors_liste(p)){
		p->ec=p->ec->pred;
	}		
}

void valeur_elt(t_liste* p, bateau_t * bat_v){
	if(!hors_liste(p)){
		*bat_v=p->ec->bateau;
	}
}

void modif_elt(t_liste* p, bateau_t * bat_v){
	if(!hors_liste(p)){	
		p->ec->bateau= *bat_v;
		(p->ec->pred)->succ= bat_v;
		(p->ec->succ)->pred= bat_v;		
	}
}

	
void oter_elt(t_liste* p){

	t_element * ancien;
	if(!hors_liste(p)){
		(p->ec->pred)->succ=p->ec->pred;
		(p->ec->succ)->pred=p->ec->succ;
		ancien=p->ec;
		p->ec=p->ec->pred;
		free(ancien);
	}
}

void ajout_droit(t_liste* p, bateau_t bat_v){
	t_element * nouveau;
	if(liste_vide(p) || !hors_liste(p)){
		nouveau=malloc(sizeof(t_element));
		nouveau->bateau = bat_v;
		nouveau->pred=p->ec;
		nouveau->succ=p->ec->succ;
		(p->ec->succ)->pred = nouveau;
		p->ec->succ= nouveau;
		p->ec = nouveau;
	}
}


void ajout_gauche(t_liste* p, bateau_t bat_v){
	t_element * nouveau;
	if(liste_vide(p) || !hors_liste(p)){
		nouveau=malloc(sizeof(t_element));
		nouveau->bateau = bat_v;
		nouveau->pred=p->ec->pred;
		nouveau->succ=p->ec;
		(p->ec->pred)->succ = nouveau;
		p->ec->pred= nouveau;
		p->ec = nouveau;
	}
}
