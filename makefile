
all : executable
executable : srv.o liste.o matricebateau.o
		gcc -o executable srv.o liste.o
srv.o : srv.c srv.h
		gcc -c srv.c
liste.o : liste.c liste.h 
		gcc -c liste.c

matricebateau.o : matricebateau.c matricebateau.h
		gcc -c matricebateau.c matricebateau.h


clean :
		rm srv.o liste.o executable core

