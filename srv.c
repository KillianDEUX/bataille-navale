#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 32000


int main(){

	struct sockaddr_in server_addr, client_addr;    
	socklen_t client_addr_len;
	int port_no=PORT;
	int i;
	int nb_cli;
	int client_fd[nb_cli];
	int choix_c_atk=1;
	int question;
	int * server_fd;
	int choix_j_atk;
	int nb_joueur;
	int nb_joueur_atk;
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
			   }
	while (nb_cli<2 || nb_cli>10);


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

   	tour_atk=1; // Le 1er joueur commence 

   	for(i=0; i<nb_cli; i++){
			send(client_fd[i], &tour_atk, sizeof(tour_atk), 0);  //Envoie le numéro du tour
	}
	printf(" -- ENVOI DU TOUR AUX CLIENTS --\n\n");  

	
	while(1){
		//choix_j_atk=0;
		//choix_c_atk=0;

		// Recoit l'action du tour : joueur qui attaque + case
		recv(client_fd[tour_atk-1], &choix_j_atk, sizeof(choix_j_atk), 0);
	    recv(client_fd[tour_atk-1], &choix_c_atk, sizeof(choix_c_atk), 0);
	    info_j_atk=choix_j_atk;
	    info_c_atk=choix_c_atk;
	    for(j=0; j<nb_cli; j++){
			send(client_fd[j], &info_j_atk, sizeof(info_j_atk), 0);
		}
		for(j=0; j<nb_cli; j++){
			send(client_fd[j], &info_c_atk, sizeof(info_c_atk), 0);
		}
	    

		printf("\n Le joueur %i attaque le joueur %i en case n° %i \n \n", tour_atk, choix_j_atk, choix_c_atk);

		if(tour_atk<nb_cli){  // Changement de tour
			tour_atk++;
		}else{
			tour_atk=1;
		}

		for(i=0; i<nb_cli; i++){
			send(client_fd[i], &tour_atk, sizeof(tour_atk), 0);	//Envoie le numéro du tour
		}
		printf(" -- ENVOI DU TOUR AUX CLIENTS --\n\n");



	}
	// }
}
	
	/**

	while(1==1){
		do{			   
			  printf("\nChoisissez le joueur à attaquer : ");
			  scanf("%i", &choix_j_atk);
			   }
		while (choix_j_atk<2 || choix_j_atk>nb_cli+1);
			
			printf("Quelle case voulez-vous attaquer ? ");
			scanf("%i", &question);
			for(i=0; i<nb_cli; i++){
			    	send(client_fd[i], &nb_joueur_atk, sizeof(nb_joueur_atk), 0);
				send(client_fd[i], &choix_j_atk, sizeof(choix_j_atk), 0);
				send(client_fd[i], &question, sizeof(question), 0);
						
			}

				

		}
		
	}**/



/**
void tcp_connection_server(int * server_fd, int * client_fd) {
    struct sockaddr_in server_addr, client_addr; 
    socklen_t client_addr_len;
    int port_no=PORT;

    int conn; //This is the connection file descriptor that will be used to distinguish client connections.
	char message[100]; //This array will store the messages that are sent by the server

	client_addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);

    //assigns the address specified by serv to the socket
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_fd,2); //Listen for client connections. Maximum 5 connections will be permitted

    printf("\n -- EN ATTENTE --\n");

	*client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

	printf("\n -- CONNECTE --\n");




			recv(client_fd[nb_cli], &choix_c_atk, sizeof(choix_c_atk), 0);


			while (choix_c_atk!=0){

				printf(" AIE ! - j'ai mal à la case : \n %i \n \n", choix_c_atk);
				choix_c_atk=0;
				printf("A mon tour, quelle case voulez-vous attaquer ? ");
				scanf("%i", &question);
				send(client_fd[nb_cli], &question, sizeof(question), 0);
				printf("\n");
			}
		    
 
}
**/
