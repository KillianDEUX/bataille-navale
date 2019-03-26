
OPTS=-g -Wall

all : executable

executable : srv.o liste.o bateau.o listebateau.o matricepion.o IA_pions.o IA_bateaux.o direction.o main.o
		gcc ${OPTS} -o executable srv.o liste.o bateau.o listebateau.o matricepion.o IA_pions.o IA_bateaux.o direction.o main.o

srv.o : srv.c
		gcc -c srv.c ${OPTS}

liste.o : liste.c liste.h bateau.h
		gcc -c liste.c -o liste.o ${OPTS}

bateau.o : bateau.c matricepion.h
		gcc -c bateau.c -o bateau.o ${OPTS}

listebateau.o : listebateau.c liste.h listebateau.h matricepion.h
		gcc -c listebateau.c -o listebateau.o ${OPTS}

matricepion.o : matricepion.c liste.h listebateau.h matricepion.h
		gcc -c matricepion.c -o matricepion.o ${OPTS}

IA_pions.o : IA_pions.c liste.h matricepion.h listebateau.h direction.h
		gcc -c IA_pions.c -o IA_pions.o ${OPTS}

IA_bateaux.o : IA_bateaux.c liste.h listebateau.h matricepion.h
		gcc -c IA_bateaux.c -o IA_bateaux.o ${OPTS}

direction.o : direction.c direction.h
		gcc -c direction.c -o direction.o ${OPTS}

main.o : main.c liste.h listebateau.h matricepion.h bateau.h
		gcc -c main.c -o main.o ${OPTS}
		
clean :
		rm  -f *.o executable
