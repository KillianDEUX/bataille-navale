#include "lettre.h"

int lettre_to_nombre(char c){
	int i;
	i = c - 65;
	return i;
}

char nombre_to_lettre(int i){
	char c;
	c = i + 65;
	return c;
}
