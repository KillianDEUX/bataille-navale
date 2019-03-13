typedef enum couleur { aucune, blanc, rouge } couleur_t;

typedef struct case_s {
	int x;
	int y;
	couleur_t c;
}case_t;

typedef enum type_bat {none, mine ,torpilleur, sousmarin,  croiseur, porteavion}type_t;
typedef enum dir_bat {aucun, vertical, horizontal}dir_t;
typedef enum etat_bat {flotte, coule}etat_t;

typedef struct bateau {
	type_t type;
	case_t coord;
	int taille;
	dir_t dir;
	etat_t etat;
	int nb_touche;
}bateau_t;


typedef struct element{
	bateau_t bateau; 
	struct element * pred; 
	struct element * succ;
}t_element;

typedef struct {
	t_element * drapeau;
	t_element * ec;
}t_liste;


void type_bateau(t_liste);
void choixbateau(t_liste,int);
void appliquer_bateau(t_liste,t_liste);
int fin_bateau_vertical(t_liste *, bateau_t *);
int fin_bateau_horizontal(t_liste *, bateau_t *);
void afficher_matrice_bateau(t_liste, int);
void cases_prises(t_liste, case_t *, int);
int placement_bateau(t_liste, bateau_t *, dir_t, case_t, int);
void placer_bateau(t_liste, int);
