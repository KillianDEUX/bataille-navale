#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 32000


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
	tour_atk=1; // Le 1er joueur commence 

   	for(i=0; i<nb_cli; i++){
			send(client_fd[i], &tour_atk, sizeof(tour_atk), 0);  //Envoie le numéro du tour
	}
	printf(" -- ENVOI DU TOUR AUX CLIENTS --\n\n");  
	
	recv(client_fd[0], &taille, sizeof(taille), 0);
	recv(client_fd[0], &nb_bateaux, sizeof(nb_bateaux), 0);
	recv(client_fd[0], &joueur1, sizeof(joueur1), 0);   // ne peut recevoir de pointeur !!!!!!!!
	switch( nb_joueurs){
		case 5 :recv(client_fd[4], &joueur5, sizeof(joueur5), 0);  // ne peut recevoir de pointeur !!!!!!!!
		case 4 :recv(client_fd[3], &joueur4, sizeof(joueur4), 0);  // ne peut recevoir de pointeur !!!!!!!!
		case 3 :recv(client_fd[2], &joueur3, sizeof(joueur3), 0);  // ne peut recevoir de pointeur !!!!!!!!
		case 2 :recv(client_fd[1], &joueur2, sizeof(joueur2), 0);  // ne peut recevoir de pointeur !!!!!!!!
		case 1 :break;
		default: printf("Erreur de joueur");
	
	}
	
	
	
	if(nb_joueurs==1){
		t_liste ia;
		appliquer_bateau(joueur1, ia);
		placer_bateau (ia, taille);
		while( !bateaux_coules(joueur1, nb_bat) || !bateaux_coules(ia, nb_bat) ){
     		
		 
		}
     
	}else{
     // TOURS DE JEU EN RESEAU
	}
}


