
all : executable

executable : srv.o liste.o matricebateau.o matricepion.o IA_pions.o IA_bateaux.o
		gcc -o executable srv.o liste.o matricebateau.o matricepion.o IA_pions.o IA_bateaux.o
		
srv.o : srv.c 
		gcc -c srv.c
		
liste.o : liste.c 
		gcc -c liste.c -o liste.o

matricebateau.o : matricebateau.c liste.h matricepion.h
		gcc -c matricebateau.c -o matricebateau.o

matricepion.o : matricepion.c liste.h
		gcc -c matricepion.c -o matricepion.o
		
IA_pions.o : IA_pions.c liste.h matricepion.h matricebateau.h
		gcc -c IA_pions.c -o IA_pions.o
		
IA_bateaux.o : IA_bateaux.c liste.h matricebateau.h
		gcc -c IA_bateaux.c -o IA_bateaux.o
		
clean :
		rm srv.o liste.o executable core

