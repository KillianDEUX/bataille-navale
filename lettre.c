#include "lettre.h"

//change le caractère fourni en paramètre en nombre
int lettre_to_nombre(char c){
	int i;
	i = c - 65;
	return i;
}

//Change le nombre fourni en paramètre en caractère
char nombre_to_lettre(int i){
	char c;
	c = i + 65;
	return c;
}
