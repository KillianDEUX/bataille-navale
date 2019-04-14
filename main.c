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
	printf("\n -- BATAILLE NAVALE EN RESEAU - DEMARRAGE DU SERVEUR --\n");


	// Definition du socket
    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);


    while( bind(*server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
    {

        server_addr.sin_port = htons(port_no);
    }

    printf("\n -- PRET - EN ATTENTE DES JOUEURS--\n\n");


    if( listen(*server_fd, nb_cli) < 0)
    {
        perror("Erorr in Listen()\n");
        exit(0);
    }

    client_addr_len = sizeof(client_addr);

	for(i=0; i<nb_cli; i++){

	nb_joueur=i;
	    client_fd[i] = accept(*server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
	    send(client_fd[i], &nb_joueur, sizeof(nb_joueur), 0); //ENVOI le no du joueur
	    printf(" -- NOUVEAU CLIENT CONNNECTE --\n\n");
	}
	printf(" -- YES ! TOUS LES JOUEURS SONT CONNECTES --\n\n");
	for(i=0; i<nb_cli; i++){
		send(client_fd[i], &nb_cli, sizeof(nb_cli), 0); //ENVOI le le nbre total de joueur
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
		matrice_pion_t mat;
		matrice_pion_t mat2;
   		matrice_pion_t mat3;
 		matrice_pion_t mat4;
  		matrice_pion_t mat5;
		matrice_case_t mat_case;
		matrice_case_t mat_case2;
		matrice_case_t mat_case3;
		matrice_case_t mat_case4;
		matrice_case_t mat_case5;
		t_liste batjoueur1;
		t_liste batjoueur2;
		t_liste batjoueur3;
		t_liste batjoueur4;
		t_liste batjoueur5;

		int ok;

		int nb_bat;
		bateau_t bat;
		coord_t cell;

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
				printf(" -- ENVOI DE LA MATRICE 5 EFFECTUEE --\n\n");
		case 4 : mat4=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat4);
				printf(" -- CREATION DE LA MATRICE 4 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat4.nbc, sizeof(mat4.nbc), 0);
					send(client_fd[i], &mat4.nbl, sizeof(mat4.nbl), 0);
					send(client_fd[i], mat4.grille[0], sizeof(case_t)*mat4.nbl*mat4.nbc, 0);
				}
				printf(" -- ENVOI DE LA MATRICE 4 EFFECTUEE --\n\n");
		case 3 : mat3=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat3);
				printf(" -- CREATION DE LA MATRICE 3 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat3.nbc, sizeof(mat3.nbc), 0);
					send(client_fd[i], &mat3.nbl, sizeof(mat3.nbl), 0);
					send(client_fd[i], mat3.grille[0], sizeof(case_t)*mat3.nbl*mat3.nbc, 0);
				}
				printf(" -- ENVOI DE LA MATRICE 3 EFFECTUEE --\n\n");
		case 2 : mat2=creer_matrice_adv (mat.nbl, mat.nbc);
				init_matrice_adv(mat2);
				printf(" -- CREATION DE LA MATRICE 2 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat2.nbc, sizeof(mat2.nbc), 0);
					send(client_fd[i], &mat2.nbl, sizeof(mat2.nbl), 0);
					send(client_fd[i], mat2.grille[0], sizeof(case_t)*mat2.nbl*mat2.nbc, 0);
				}
				printf(" -- ENVOI DE LA MATRICE 2 EFFECTUEE --\n\n");
				for(i=0; i<nb_cli; i++){
					send(client_fd[i], &mat.nbc, sizeof(mat.nbc), 0);
					send(client_fd[i], &mat.nbl, sizeof(mat.nbl), 0);
					send(client_fd[i], mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);
				}
				printf(" -- ENVOI DE LA MATRICE 1 EFFECTUEE --\n\n");
		default : break;
	}

	printf(" -- ENVOI DES MATRICES TERMINEE --\n\n");

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
		printf(" -- EN ATTENTE DE RECEPTION BATEAU JOUEUR 1 --\n\n");

	mat_case=creer_matrice_joueur( mat.nbl, mat.nbc );
	init_matrice_joueur(mat_case);
	init_liste(&batjoueur1);
	recv(client_fd[0], &mat_case.nbc, sizeof(mat_case.nbc), 0);
	recv(client_fd[0], &mat_case.nbl, sizeof(mat_case.nbl), 0);
	recv(client_fd[0], mat_case.grille[0], sizeof(case_t)*mat_case.nbl*mat_case.nbc, 0);
	recv(client_fd[0], &nb_bat, sizeof(int), 0);
 for(int i=0; i<nb_bat; i++){
		recv(client_fd[0], &bat.type, sizeof(type_t), 0);
		recv(client_fd[0], &bat.coord.x, sizeof(int), 0);
		recv(client_fd[0], &bat.coord.y, sizeof(int), 0);
		recv(client_fd[0], &bat.taille, sizeof(int), 0);
		recv(client_fd[0], &bat.dir, sizeof(dir_t), 0);
		recv(client_fd[0], &bat.etat, sizeof(etat_t),0);
		recv(client_fd[0], &bat.nb_touche, sizeof(int), 0);
		placement_bateau( batjoueur1, &bat, bat.dir, bat.coord, mat_case);
	}

	printf("Affichage de la flotte du joueur 1 \n \n");
	affichage_flotte(batjoueur1, mat_case);

	printf(" -- ENVOI DES LISTES DE BATEAUX AUX CLIENTS --\n\n");
	for(i=1; i<nb_cli; i++){
		send(client_fd[i], &mat_case.nbc, sizeof(mat_case.nbc), 0);
		send(client_fd[i], &mat_case.nbl, sizeof(mat_case.nbl), 0);
		send(client_fd[i], mat_case.grille[0], sizeof(case_t)*mat_case.nbl*mat_case.nbc, 0);
		send(client_fd[i], &nb_bat, sizeof(int), 0);
		for(en_tete(&batjoueur1); !hors_liste(&batjoueur1); suivant(&batjoueur1)){
			valeur_elt(&batjoueur1, &bat);
			send(client_fd[i], &bat.type, sizeof(type_t), 0);
			send(client_fd[i], &bat.coord.x, sizeof(int), 0);
			send(client_fd[i], &bat.coord.y, sizeof(int), 0);
			send(client_fd[i], &bat.taille, sizeof(int), 0);
			send(client_fd[i], &bat.dir, sizeof(dir_t), 0);
			send(client_fd[i], &bat.etat, sizeof(etat_t), 0);
			send(client_fd[i], &bat.nb_touche, sizeof(int), 0);
		}
	}
	printf(" -- ENVOI TERMINEE --\n\n");

	for(int i=1; i<nb_cli; i++){
			recv(client_fd[i], &ok, sizeof(int), 0);
	}

     switch(nb_cli){
          case 5 :
                    mat_case5=creer_matrice_joueur( mat5.nbl, mat5.nbc );
              		init_matrice_joueur(mat_case5);
              		init_liste(&batjoueur5);
                    recv(client_fd[4], &mat_case5.nbc, sizeof(mat_case5.nbc), 0);
                    recv(client_fd[4], &mat_case5.nbl, sizeof(mat_case5.nbl), 0);
                    recv(client_fd[4], mat_case5.grille[0], sizeof(case_t)*mat_case5.nbl*mat_case5.nbc, 0);
                    recv(client_fd[4], &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur5); !hors_liste(&batjoueur5); suivant(&batjoueur5)){
                      valeur_elt(&batjoueur5, &bat);
                      recv(client_fd[4], &bat.type, sizeof(type_t), 0);
                      recv(client_fd[4], &bat.coord.x, sizeof(int), 0);
                      recv(client_fd[4], &bat.coord.y, sizeof(int), 0);
                      recv(client_fd[4], &bat.taille, sizeof(int), 0);
                      recv(client_fd[4], &bat.dir, sizeof(dir_t), 0);
                      recv(client_fd[4], &bat.etat, sizeof(etat_t), 0);
                      recv(client_fd[4], &bat.nb_touche, sizeof(int), 0);
                    }
                    printf("Affichage de la flotte du joueur 5 \n \n");
					affichage_flotte(batjoueur5, mat_case5);

          case 4 :
                  	mat_case4=creer_matrice_joueur( mat4.nbl, mat4.nbc);
              		init_matrice_joueur(mat_case4);
              		init_liste(&batjoueur4);
                    recv(client_fd[3], &mat_case4.nbc, sizeof(mat_case4.nbc), 0);
                    recv(client_fd[3], &mat_case4.nbl, sizeof(mat_case4.nbl), 0);
                    recv(client_fd[3], mat_case4.grille[0], sizeof(case_t)*mat_case4.nbl*mat_case4.nbc, 0);
                    recv(client_fd[3], &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur4); !hors_liste(&batjoueur4); suivant(&batjoueur4)){
                      valeur_elt(&batjoueur4, &bat);
                      recv(client_fd[3], &bat.type, sizeof(type_t), 0);
                      recv(client_fd[3], &bat.coord.x, sizeof(int), 0);
                      recv(client_fd[3], &bat.coord.y, sizeof(int), 0);
                      recv(client_fd[3], &bat.taille, sizeof(int), 0);
                      recv(client_fd[3], &bat.dir, sizeof(dir_t), 0);
                      recv(client_fd[3], &bat.etat, sizeof(etat_t), 0);
                      recv(client_fd[3], &bat.nb_touche, sizeof(int), 0);
                    }
                    printf("Affichage de la flotte du joueur 4 \n \n");
					affichage_flotte(batjoueur4, mat_case4);
          case 3 :
                    mat_case3=creer_matrice_joueur( mat3.nbl, mat3.nbc );
              		init_matrice_joueur(mat_case3);
              		init_liste(&batjoueur3);
                    recv(client_fd[2], &mat_case3.nbc, sizeof(mat_case3.nbc), 0);
                    recv(client_fd[2], &mat_case3.nbl, sizeof(mat_case3.nbl), 0);
                    recv(client_fd[2], mat_case3.grille[0], sizeof(case_t)*mat_case3.nbl*mat_case3.nbc, 0);
                    recv(client_fd[2], &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur3); !hors_liste(&batjoueur3); suivant(&batjoueur3)){
                      valeur_elt(&batjoueur3, &bat);
                      recv(client_fd[2], &bat.type, sizeof(type_t), 0);
                      recv(client_fd[2], &bat.coord.x, sizeof(int), 0);
                      recv(client_fd[2], &bat.coord.y, sizeof(int), 0);
                      recv(client_fd[2], &bat.taille, sizeof(int), 0);
                      recv(client_fd[2], &bat.dir, sizeof(dir_t), 0);
                      recv(client_fd[2], &bat.etat, sizeof(etat_t), 0);
                      recv(client_fd[2], &bat.nb_touche, sizeof(int), 0);
                    }
                    printf("Affichage de la flotte du joueur 3 \n \n");
					affichage_flotte(batjoueur3, mat_case3);

          case 2 :
          			mat_case2=creer_matrice_joueur( mat2.nbl, mat2.nbc );
              		init_matrice_joueur(mat_case2);
              		init_liste(&batjoueur2);
                    recv(client_fd[1], &mat_case2.nbc, sizeof(mat_case2.nbc), 0);
                    recv(client_fd[1], &mat_case2.nbl, sizeof(mat_case2.nbl), 0);
                    recv(client_fd[1], mat_case2.grille[0], sizeof(case_t)*mat_case2.nbl*mat_case2.nbc, 0);
                    recv(client_fd[1], &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur2); !hors_liste(&batjoueur2); suivant(&batjoueur2)){
                      valeur_elt(&batjoueur2, &bat);
                      recv(client_fd[1], &bat.type, sizeof(type_t), 0);
                      recv(client_fd[1], &bat.coord.x, sizeof(int), 0);
                      recv(client_fd[1], &bat.coord.y, sizeof(int), 0);
                      recv(client_fd[1], &bat.taille, sizeof(int), 0);
                      recv(client_fd[1], &bat.dir, sizeof(dir_t), 0);
                      recv(client_fd[1], &bat.etat, sizeof(etat_t), 0);
                      recv(client_fd[1], &bat.nb_touche, sizeof(int), 0);
                    }

                    printf("Affichage de la flotte du joueur 2 \n \n");
					affichage_flotte(batjoueur2, mat_case2);
              break;

          default : break;
        }

	for(int i=1; i<nb_cli; i++){
			recv(client_fd[i], &ok, sizeof(int), 0);
	}

	while(1){

	printf(" -- ENVOI DU TOUR AUX CLIENTS --\n\n");
	for(i=0; i<nb_cli; i++){
		send(client_fd[i], &tour_atk, sizeof(tour_atk), 0);  //ENVOI le numéro du tour
	}

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
	cell.x=choix_c_atk-1;
	cell.y=choix_c_atk2-1;

	switch(choix_j_atk){
		case 5 :switch (nb_cli){
					case 5: 
					case 4: ajout_pion_matrice( cell, mat_case, mat4, batjoueur1 );
					case 3: ajout_pion_matrice( cell, mat_case, mat3, batjoueur1 );
					case 2: ajout_pion_matrice( cell, mat_case, mat2, batjoueur1 );
							ajout_pion_matrice( cell, mat_case, mat, batjoueur1 );

				}
				break;

		case 4 :switch (nb_cli){
					case 5: ajout_pion_matrice( cell, mat_case, mat5, batjoueur1 );
					case 4: 
					case 3: ajout_pion_matrice( cell, mat_case, mat3, batjoueur1 );
					case 2: ajout_pion_matrice( cell, mat_case, mat2, batjoueur1 );
							ajout_pion_matrice( cell, mat_case, mat, batjoueur1 );

				}
				break;


		case 3 :switch (nb_cli){
					case 5: ajout_pion_matrice( cell, mat_case, mat5, batjoueur1 );
					case 4: ajout_pion_matrice( cell, mat_case, mat4, batjoueur1 );
					case 3:
					case 2: ajout_pion_matrice( cell, mat_case, mat2, batjoueur1 );
							ajout_pion_matrice( cell, mat_case, mat, batjoueur1 );

				}
				break;

		case 2 :switch (nb_cli){
					case 5: ajout_pion_matrice( cell, mat_case, mat5, batjoueur1 );
					case 4: ajout_pion_matrice( cell, mat_case, mat4, batjoueur1 );
					case 3: ajout_pion_matrice( cell, mat_case, mat3, batjoueur1 );
					case 2: ajout_pion_matrice( cell, mat_case, mat, batjoueur1 );
				}
				break;

		case 1 : switch (nb_cli){
					case 5: ajout_pion_matrice( cell, mat_case, mat5, batjoueur1 );
					case 4: ajout_pion_matrice( cell, mat_case, mat4, batjoueur1 );
					case 3: ajout_pion_matrice( cell, mat_case, mat3, batjoueur1 );
					case 2: ajout_pion_matrice( cell, mat_case, mat2, batjoueur1 );
				}
				break;

		default : break;
	}

	if(tour_atk<nb_cli){  // Changement de tour
		tour_atk++;
	}else{
		tour_atk=1;
	}
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
	matrice_pion_t mat;
	matrice_pion_t mat_ia;
	matrice_case_t mat_case;
	matrice_case_t mat_case_ia;
	int choix_c_atk = -1;
	int choix_c_atk2 = -1;
	int nb_bat;
	coord_t cell;
	coord_t tir;

	if(nbj==1){ // si le mode de jeu est solo
		t_liste ia;
		init_liste(&ia);
		mat=choixgrille(mat);  //le joueur choisi la taille de la grille
		init_matrice_adv(mat); //initilisation de cette matrice pion
		mat_ia=creer_matrice_adv (mat.nbl, mat.nbc); //Creation de la matrice pion de l'ia
		init_matrice_adv(mat_ia); //initilisation de cette matrice
		mat_case=creer_matrice_joueur( mat.nbl, mat.nbc ); //Creation de la matrice du joueur
		init_matrice_joueur(mat_case); //initilisation de cette matrice
		mat_case_ia=creer_matrice_joueur( mat.nbl, mat.nbc ); //Creation de la matrice de l'ia
		init_matrice_joueur(mat_case_ia); //Creation de la matrice de l'ia
		afficher_matrice_pion(mat); //affichage de la matrice pion
		nb_bat=choixbateau(batjoueur1, mat_case); //le joueur choisit les bateaux et leurs tailles
		placer_bateau_ia(batjoueur1 ,mat_case_ia, ia); //le joueur choisit où les placer
		//printf("Affichage de la grille de l'IA\n");
		//affichage_flotte(ia, mat_case_ia);
		en_tete(&batjoueur1);
		bateau_t bateau;
		valeur_elt(&batjoueur1,&bateau);
		while(!bateaux_coules(batjoueur1, nb_bat) && !bateaux_coules(ia, nb_bat)){ //boucle tant que les bateaux du joueur OU de l'ia ne sont pas tous coulés
			do{
				printf("\n A votre tour, \nQuelle case voulez-vous attaquer ( de la forme \"ligne colonne\")? ");
				scanf("%i %i", &choix_c_atk, &choix_c_atk2);
				if(choix_c_atk<=0 || choix_c_atk2<=0 || choix_c_atk>mat.nbl || choix_c_atk2>mat.nbc){
					printf("Cette case n'est pas dans la grille\n");
				}
				if( choix_c_atk>0 && choix_c_atk2>0 && choix_c_atk<=mat.nbl && choix_c_atk2<=mat.nbc && mat.grille[choix_c_atk-1][choix_c_atk2-1].c!= AUCUNE){
					printf("Cette case à déjà été selectionnée !");
				}
			}while( choix_c_atk<=0 || choix_c_atk2<=0 || choix_c_atk>mat.nbl || choix_c_atk2>mat.nbc || mat.grille[choix_c_atk-1][choix_c_atk2-1].c!= AUCUNE); //Verification que le tir est dans les normes 
			cell.x=choix_c_atk-1;
			cell.y=choix_c_atk2-1;
			afficher_legende();
			printf("Affichage de votre tir :\n");
			ajout_pion_matrice( cell, mat_case_ia, mat, ia );
			afficher_matrice_pion(mat);
			printf("Au tour de l'IA\n");
			tir=choisir_case(mat_ia,batjoueur1);
			ajout_pion_matrice( tir , mat_case, mat_ia, batjoueur1 );
			printf("Affichage de votre plateau :\n");
			affichage_flotte(batjoueur1, mat_case);
			//afficher_matrice_pion(mat_ia);
			//affichage_flotte(ia, mat_case_ia);
		}
		if(bateaux_coules(batjoueur1, nb_bat)){
			printf("L'IA a gagnée \n");
		}
		else if(bateaux_coules(ia, nb_bat)){
			printf("Bien joué vous avez gagné \n");
		}
		else{
			printf("Il y a égalité");
		}
	}
	else{
     		partie_reseau(nbj);
	}
	return 0;
}
