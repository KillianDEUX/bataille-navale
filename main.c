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
#include "IA_bateaux.h"
#include "IA_pions.h"


// creer la grille en fonction des choix du joueur
matrice_t choixgrille(matrice_t mat){
	int nbli,nbco; // taille de la grille de jeu (nb de lignes/ nb de colonnes) 
	do{
		printf("Quel est la largeur de la grille (entre 5 et 32)\n");
		scanf("%d",&nbco);
		if(nbco<5 || nbco>32){
			printf("Largeur de la grille non conforme\n");
		}
	}while(nbco<5 || nbco>32);
	do{
		printf("Quel est la hauteur de la grille (entre 5 et 32)\n");
		scanf("%d",&nbli);
		if(nbli<5 || nbli>32){
			printf("Hauteur de la grille non conforme\n");
		}
	}while(nbli<5 || nbli>32); // pour une taille max de grille de 1024
	mat=creer_matrice_adv(nbli, nbco);
	mat.nbc=nbco;
	mat.nbl=nbli;
	return mat;
}



void connexion( int nb_cli){
	struct sockaddr_in server_addr, client_addr;    
	socklen_t client_addr_len;
	int port_no=PORT;
	int i;
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

}


int main( ){

	int nbj;// nombre de joueurs
	
	do{			// demande du nb de joueurs
		printf("Quel est le nombre de joueurs ?(inferieur à 5)\n");
		scanf("%d",&nbj);
	}while( nbj<1 || nbj>5);
	
	t_liste joueur1; 
	matrice_t mat;
	
	if(nbj==1){ // si le mode de jeu est solo
		t_liste ia;
		
		mat=choixgrille(mat);
		init_matrice_adv(mat);
		afficher_matrice_pion(mat);
		choixbateau(joueur1, mat);
		appliquer_bateau(joueur1,ia);
		placer_bateau_ia(joueur1 ,mat ,ia);
		placer_bateau(joueur1, mat);
		affichage_flotte(joueur1, mat);
		affichage_flotte(ia, mat);
		
		//appliquer_bateau(joueur1, ia);
		//placer_bateau (ia, mat);
		//while( !bateaux_coules(joueur1, nb_bat) || !bateaux_coules(ia, nb_bat) ){
     		
		 
		//}
     
	}else{
     connexion(nbj);
     int tour_atk=1; // Le 1er joueur commence 
	}
	return 0;
}


