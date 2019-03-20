#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 32000
#include "bateau.h"
#include "matricepion.h"
#include "liste.h"
#include "listebateau.h"
#define TAILLE_MAT_DEF 10


int connexion(){
	struct sockaddr_in server_addr, client_addr;    
	socklen_t client_addr_len;
	int port_no=PORT;
	int i;
	int nb_cli=0;
	int client_fd[nb_cli];
	int choix_c_atk=1;
	int * server_fd;
	int choix_j_atk;
	int nb_joueur;
	server_fd = malloc(sizeof(int));
	int tour_atk;

	int info_j_atk;
	int info_c_atk;
	int j;

	system("clear");
	printf("\n -- BATAILLE NAVALE EN RESEAU - SERVEUR --\n");

	do{			   
		printf("\n Bonjour ! A combien voulez-vous jouer aujoud'hui ? ");
			    scanf("%i", &nb_cli);
	}while (nb_cli<2 || nb_cli>10);


	// Definition du socket
    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);


    while( bind(*server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
    {

        server_addr.sin_port = htons(port_no);
    }

    printf("\n -- EN ATTENTE DES JOUEURS--\n\n");

  
    if( listen(*server_fd, nb_cli) < 0)
    {
        perror("Erorr in Listen()\n");
        exit(0);
    }

    client_addr_len = sizeof(client_addr);

	for(i=0; i<nb_cli; i++){

	nb_joueur=i;
	    client_fd[i] = accept(*server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
	    send(client_fd[i], &nb_joueur, sizeof(nb_joueur), 0); //Envoie le no du joueur
	    printf(" -- NOUVEAU CLIENT CONNNECTE --\n\n");
	}
	printf(" -- YES ! TOUS LES JOUEURS SONT CONNECTES --\n\n");
	for(i=0; i<nb_cli; i++){
		send(client_fd[i], &nb_cli, sizeof(nb_cli), 0); //Envoie le le nbre total de joueur
	}
	printf(" -- ENVOI DE NB_CLI AUX CLIENTS --\n\n");

	return nb_cli;
}


int main( ){
	int taille= TAILLE_MAT_DEF ;
	int nb_joueurs=connexion();	
	int tour_atk=1; // Le 1er joueur commence 
	t_liste joueur1;
	matrice_t mat;
	
	if(nb_joueurs==1){
		t_liste ia;
		appliquer_bateau(joueur1, ia);
		placer_bateau (ia, mat);
		//while( !bateaux_coules(joueur1, nb_bat) || !bateaux_coules(ia, nb_bat) ){
     		
		 
		//}
     
	}else{
     // TOURS DE JEU EN RESEAU
	}
	return 0;
}


