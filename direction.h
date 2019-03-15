
#include "liste.h" //pour case_t

typedef enum { NORD=0, EST, SUD, OUEST} direction_t;
const int NB_DIRECTION=4;


case_t direction_avancer(direction_t, case_t, int);

direction_t direction_suivante(direction_t);

direction_t direction_debut();

char* direction_str(direction_t);

