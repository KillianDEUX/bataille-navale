
#include <stdio.h>
#include <stdlib.h>

void modif_type_bat(bateau_t actuel){
	if(actuel->taille == 1){
		actuel->type = mine;
	}
	if(actuel->taille == 2){
		actuel->type = torpilleur;
	}
	if(actuel->taille == 3){
		actuel->type = sousmarin;
	}
	if(actuel->taille == 4){
		actuel->type = croiseur;
	}
	if(actuel->taille == 5){
		actuel->type = porteavion;
	}
}

int fin_bateau_vertical(bateau_t *bateau){ 
	return (bateau->coord.y + bateau->taille);
}
       
int fin_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille); 
}

void afficher_bateau(bateau_t actuel, int i, int j){
		if(i==actuel->coord.x && j==actuel->coord.y){
	       	if(actuel->dir == vertical){
	       		for(int k=j; k< (fin_bateau_vertical(actuel)); k++){
	       			printf("[.]");
	       		}
	       	}
	       	if(actuel->dir == horizontal){
	       		for(int k=j; k< (fin_bateau_horizontal(actuel)); k++){
	       			printf("[.]");
	       		}
	       	}
	    }
	    else{
	       	printf("[ ]");
	    }
}


void cases_nondisponibles(case_t * cases_nonlibres,bateau_t *bat, case_t actuel, int compteur ,int taille){
		int i;
		if(bat->dir == vertical){
	       		fin_bat = fin_bateau_vertical(bat);
	       		for(i=bat->coord.y,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.y){ 
					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x++;		
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
			}
		}
		if(bat->dir == horizontal){
			fin_bat = fin_bateau_horizontal(bat);
       			for(i=bat->coord.x,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.x){ 
					actuel.y--;
					if(danslagrille(taille, actuel)){	
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
			}			
		}
}


void verif_placement_bateau(bateau_t * bat, case_t *casesprises, int * result){
	int i, j;
		if(dir == vertical){
			for(i=emp.y; i<(bat->taille+emp.y) && result; i++){
				for(j=0; casesprises[j].y != -1 && result; j++){
					if(casesprises[j].y == i && casesprises[j].x == emp.x){
						printf("Erreur : le bateau ne peut pas être placé ici");
						result = 0;
					}
				}
			}
		}
		else {//if(dir == horizontal){
			for(i=emp.x; i<(bat->taille+emp.x) && result; i++){
				for(j=0; casesprises[j].x != -1 && result; j++){
					if(casesprises[j].x == i && casesprises[j].y == emp.y){
						printf("Erreur : le bateau ne peut pas être placé ici");
						result = 0;
					}
				}
			}
		}
}

void implanter_coordonnee_bateau(bateau_t * bat, case_t emp, dir_t dir){
	bat->coord.x = emp.x;
	bat->coord.y = emp.y;
	bat->dir = dir;
	bat->etat = flotte;
	bat->nb_touche = 0;
}

void implanter_nouveau_bateau(int t, bateau_t nouveau){
	nouveau.taille = t;
	nouveau.coord.x = -1;
	nouveau.coord.y = -1;
	nouveau.dir = aucun;
	nouveau.type = aucun;
	nouveau.etat = flotte;
	nouveau.nb_touche = 0;
}


// verifie si le bateau est coulé
int bat_coul(bateau_t bateau, int nb_bat){
	if( bateau->etat=coule){
		return 1;
	}
	return 0;
}



// renvoie 2 si coulé, 1 si touché et 0 si dans l'eau
int toucheunbateau( int taille, case_t cell, bateau_t actueltemp){
		if (cell.x== actueltemp->coord->x && cell.y == actueltemp->coord->y){
					actueltemp->nb_touche++;
					if(actueltemp->nb_touche == actueltemp->taille){
						actueltemp->etat = coule;
						return 2;
					}
					return 1;
				}
		return 0;
}
