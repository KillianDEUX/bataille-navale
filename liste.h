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


void init_liste(t_liste*);
int liste_vide(t_liste*);
int hors_liste(t_liste*);
void en_tete(t_liste*);
void en_queue(t_liste*);
void precedent(t_liste*);
void suivant(t_liste*);
void valeur_elt(t_liste*, bateau_t *);
void modif_elt(t_liste*, bateau_t *);
void oter_elt(t_liste*);
void ajout_droit(t_liste*, bateau_t);
void ajout_gauche(t_liste*, bateau_t);

