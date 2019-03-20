
all : executable

executable : srv.o liste.o bateau.o listebateau.o matricepion.o IA_pions.o IA_bateaux.o direction.o commun.o main.o
		gcc -o executable srv.o liste.o bateau.o listebateau.o matricepion.o IA_pions.o IA_bateaux.o direction.o main.o

srv.o : srv.c
		gcc -c srv.c

liste.o : liste.c liste.h bateau.h
		gcc -c liste.c -o liste.o

bateau.o : bateau.c matricepion.h
		gcc -c bateau.c -o bateau.o

listebateau.o : listebateau.c liste.h listebateau.h matricepion.h
		gcc -c listebateau.c -o listebateau.o

matricepion.o : matricepion.c liste.h listebateau.h matricepion.h
		gcc -c matricepion.c -o matricepion.o

IA_pions.o : IA_pions.c liste.h matricepion.h listebateau.h
		gcc -c IA_pions.c -o IA_pions.o

IA_bateaux.o : IA_bateaux.c liste.h listebateau.h matricepion.h
		gcc -c IA_bateaux.c -o IA_bateaux.o

direction.o : direction.c direction.h
		gcc -c direction.c -o direction.o

main.o : main.c liste.h listebateau.h matricepion.h bateau.h direction.h
		gcc -c main.c -o main.o
		
clean :
		rm srv.o liste.o executable core
