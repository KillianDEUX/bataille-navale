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
#include "matrice.h"





void partie_reseau( int nb_cli){


	/************************************* Connection ********************************************/


	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	int port_no=PORT;
	int i;
	int client_fd[nb_cli];
	int * server_fd;
	int nb_joueur;
	server_fd = malloc(sizeof(int));

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




/********************************Debut de la partie en réseau **********************************/

	int tour_atk=1; // Le 1er joueur commence
	int info_j_atk;
	int info_c_atk;
	int info_c_atk2;
	int choix_j_atk;
	int choix_c_atk;
	int choix_c_atk2;
	int j;
	matrice_t mat;
	matrice_t mat2;
    matrice_t mat3;
    matrice_t mat4;
    matrice_t mat5;

	recv(client_fd[0], &mat.nbc, sizeof(mat.nbc), 0);
	recv(client_fd[0], &mat.nbl, sizeof(mat.nbl), 0);
	mat=creer_matrice_adv(mat.nbl, mat.nbc);
	recv(client_fd[0], mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);

	printf(" -- RECEPTION DE LA MATRICE --\n\n");

	switch(nb_cli){
		case 5 : mat5=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat5);
				printf(" -- CREATION DE LA MATRICE 5 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat5.nbc, sizeof(mat5.nbc), 0);
					send(client_fd[i], &mat5.nbl, sizeof(mat5.nbl), 0);
					send(client_fd[i], mat5.grille[0], sizeof(case_t)*mat5.nbl*mat5.nbc, 0);
				}
				printf(" -- ENVOIE DE LA MATRICE 5 EFFECTUEE --\n\n");
		case 4 : mat4=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat4);
				printf(" -- CREATION DE LA MATRICE 4 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat4.nbc, sizeof(mat4.nbc), 0);
					send(client_fd[i], &mat4.nbl, sizeof(mat4.nbl), 0);
					send(client_fd[i], mat4.grille[0], sizeof(case_t)*mat4.nbl*mat4.nbc, 0);
				}
				printf(" -- ENVOIE DE LA MATRICE 4 EFFECTUEE --\n\n");
		case 3 : mat3=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat3);
				printf(" -- CREATION DE LA MATRICE 3 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat3.nbc, sizeof(mat3.nbc), 0);
					send(client_fd[i], &mat3.nbl, sizeof(mat3.nbl), 0);
					send(client_fd[i], mat3.grille[0], sizeof(case_t)*mat3.nbl*mat3.nbc, 0);
				}
				printf(" -- ENVOIE DE LA MATRICE 3 EFFECTUEE --\n\n");
		case 2 : mat2=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat2);
				printf(" -- CREATION DE LA MATRICE 2 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat2.nbc, sizeof(mat2.nbc), 0);
					send(client_fd[i], &mat2.nbl, sizeof(mat2.nbl), 0);
					send(client_fd[i], mat2.grille[0], sizeof(case_t)*mat2.nbl*mat2.nbc, 0);
				}
				printf(" -- ENVOIE DE LA MATRICE 2 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat.nbc, sizeof(mat.nbc), 0);
					send(client_fd[i], &mat.nbl, sizeof(mat.nbl), 0);
					send(client_fd[i], mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);
				}
				printf(" -- ENVOIE DE LA MATRICE 1 EFFECTUEE --\n\n");
		default : break;
	}

	printf(" -- ENVOIE DES MATRICES TERMINEE --\n\n");

	printf(" -- AFFICHAGE DES MATRICES--\n\n");

	switch(nb_cli){
		case 5 :printf(" Affichage de la grille de l'adversaire 5 \n\n");
				afficher_matrice_pion(mat5);

		case 4 :printf(" Affichage de la grille de l'adversaire 4 \n\n");
				afficher_matrice_pion(mat4);

		case 3 :printf(" Affichage de la grille de l'adversaire 3 \n\n");
				afficher_matrice_pion(mat3);

		case 2 :printf(" Affichage de la grille de l'adversaire 2 \n\n");
				afficher_matrice_pion(mat2);
				printf(" Affichage de la grille de l'adversaire 1 \n\n");
				afficher_matrice_pion(mat);

		default : break;
	}

	printf(" -- AFFICHAGE DES MATRICES TERMINEE --\n\n");


	for(i=0; i<nb_cli; i++){
		send(client_fd[i], &tour_atk, sizeof(tour_atk), 0);  //Envoie le numéro du tour
	}
	printf(" -- ENVOI DU TOUR AUX CLIENTS --\n\n");


	while(1){

	// Recoit l'action du tour : joueur qui attaque
	if(nb_cli!=2){
		recv(client_fd[tour_atk-1], &choix_j_atk, sizeof(choix_j_atk), 0);
		info_j_atk=choix_j_atk;
	}else{
		if(tour_atk==1){
			info_j_atk=2;
			choix_j_atk=2;
		}else{
			info_j_atk=1;
			choix_j_atk=1;

		}
	}

	// Recoit l'action du tour :  case

		recv(client_fd[tour_atk-1], &choix_c_atk, sizeof(choix_c_atk), 0);
		recv(client_fd[tour_atk-1], &choix_c_atk2, sizeof(choix_c_atk2), 0);
		info_c_atk=choix_c_atk;
		info_c_atk2=choix_c_atk2;
		for(j=0; j<nb_cli; j++){
			send(client_fd[j], &info_j_atk, sizeof(info_j_atk), 0);
		}
		for(j=0; j<nb_cli; j++){
			send(client_fd[j], &info_c_atk, sizeof(info_c_atk), 0);
		}
		for(j=0; j<nb_cli; j++){
			send(client_fd[j], &info_c_atk2, sizeof(info_c_atk2), 0);
		}


	printf("\n Le joueur %i attaque le joueur %i en case n° %i %i\n \n", tour_atk, choix_j_atk, choix_c_atk, choix_c_atk2);

	

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


}

int main( ){

	int nbj;// nombre de joueurs

	do{			// demande du nb de joueurs
		printf("Quel est le nombre de joueurs ?(inferieur à 5)\n");
		scanf("%d",&nbj);
	}while( nbj<1 || nbj>5);

	t_liste batjoueur1;
	init_liste(&batjoueur1);
	matrice_t mat;

	if(nbj==1){ // si le mode de jeu est solo
		//t_liste ia;

		mat=choixgrille(mat);
		init_matrice_adv(mat);
		afficher_matrice_pion(mat);
		choixbateau(batjoueur1, mat);
		//appliquer_bateau(batjoueur1,ia);
		//placer_bateau_ia(batjoueur1 ,mat ,ia);
		affichage_flotte(batjoueur1, mat);
		//affichage_flotte(ia, mat);

		//appliquer_bateau(batjoueur1, ia);
		//placer_bateau (ia, mat);
		//while( !bateaux_coules(batjoueur1, nb_bat) || !bateaux_coules(ia, nb_bat) ){


		//}

	}else{
     partie_reseau(nbj);
	}
	return 0;
}
