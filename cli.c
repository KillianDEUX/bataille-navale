#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#define PORT 32000
#define ip "127.0.0.1"
#include "bateau.h"
#include "matricepion.h"
#include "liste.h"
#include "listebateau.h"
#include "IA_bateaux.h"
#include "IA_pions.h"
#include "matrice.h"



void tcp_connection_client(int * client_fd)
{
    struct sockaddr_in serv_addr;
    int port_no=PORT;
    //char *ip = malloc(200);

    printf("\n Entrez l'@IP du serveur : DEJA FAIT ");
	//scanf("%s", ip);




    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port_no);


    if( connect(*client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connexion impossible, verifiez que le serveur est démarré ! \n");
        exit(0);
    }
    printf("\n -- CONNECTE -- \n");
}

int main() {
	system("clear");
	printf("\n -- BATAILLE NAVALE EN RESEAU - CLIENT --\n");

    int choix_c_atk = -1;
    int choix_c_atk2 = -1;
    int question;
    int server_fd, client_fd;
    int nb_cli;
    int nb_joueur;
  	int tour_atk;
  	int choix_j_atk;
  	int i;
  	int nb_joueur_atk;
  	int info_j_atk;
  	int info_c_atk;
  	int info_c_atk2;
    matrice_pion_t mat;
    matrice_pion_t mat2;
    matrice_pion_t mat3;
    matrice_pion_t mat4;
    matrice_pion_t mat5;
    t_liste batjoueur1;
    init_liste(&batjoueur1);
    int nb_bat;
    matrice_case_t mat_case;
    matrice_case_t mat_case2;
    matrice_case_t mat_case3;
    matrice_case_t mat_case4;
    matrice_case_t mat_case5;
    bateau_t bat;
    t_liste batjoueur_np;
    init_liste(&batjoueur_np);
    t_liste batjoueur5;
    t_liste batjoueur4;
    t_liste batjoueur3;
    t_liste batjoueur2;
    int ok=1;





    tcp_connection_client(&client_fd);
    recv(client_fd, &nb_joueur, sizeof(nb_joueur), 0);
    recv(client_fd, &nb_cli, sizeof(nb_cli), 0);




    printf("\n La partie est constituée de %i joueurs \n", nb_cli);
    printf("\n Tu es le joueur %i \n", nb_joueur+1);

     //Choix de la grille
    if(nb_joueur+1==1){
      mat=choixgrille(mat);
      init_matrice_adv(mat);
      send(client_fd, &mat.nbc, sizeof(mat.nbc), 0);
      send(client_fd, &mat.nbl, sizeof(mat.nbl), 0);
      send(client_fd, mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);
    }
    printf(" \n ----------------------------------------------------------------------------- \n");

    switch(nb_cli){
		case 5 :recv(client_fd, &mat5.nbc, sizeof(mat5.nbc), 0);
				recv(client_fd, &mat5.nbl, sizeof(mat5.nbl), 0);
        mat5=creer_matrice_adv(mat5.nbl, mat5.nbc);
				recv(client_fd, mat5.grille[0], sizeof(case_t)*mat5.nbl*mat5.nbc, 0);

		case 4 :recv(client_fd, &mat4.nbc, sizeof(mat4.nbc), 0);
				recv(client_fd, &mat4.nbl, sizeof(mat4.nbl), 0);
        mat4=creer_matrice_adv(mat4.nbl, mat4.nbc);
				recv(client_fd, mat4.grille[0], sizeof(case_t)*mat4.nbl*mat4.nbc, 0);

		case 3 :recv(client_fd, &mat3.nbc, sizeof(mat3.nbc), 0);
				recv(client_fd, &mat3.nbl, sizeof(mat3.nbl), 0);
        mat3=creer_matrice_adv(mat3.nbl, mat3.nbc);
				recv(client_fd, mat3.grille[0], sizeof(case_t)*mat3.nbl*mat3.nbc, 0);

		case 2 :recv(client_fd, &mat2.nbc, sizeof(mat2.nbc), 0);
				recv(client_fd, &mat2.nbl, sizeof(mat2.nbl), 0);
        mat2=creer_matrice_adv(mat2.nbl, mat2.nbc);
				recv(client_fd, mat2.grille[0], sizeof(case_t)*mat2.nbl*mat2.nbc, 0);

				recv(client_fd, &mat.nbc, sizeof(mat.nbc), 0);
				recv(client_fd, &mat.nbl, sizeof(mat.nbl), 0);
        mat=creer_matrice_adv(mat.nbl, mat.nbc);
				recv(client_fd, mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);

		default : break;
	}
	switch(nb_cli){
		case 5 : if(nb_joueur+1!=5){
					printf(" Affichage de la grille de l'adversaire 5 \n\n");
					afficher_matrice_pion(mat5);
				}

		case 4 :if(nb_joueur+1!=4){
					printf(" Affichage de la grille de l'adversaire 4 \n\n");
					afficher_matrice_pion(mat4);
				}

		case 3 :if(nb_joueur+1!=3){
					printf(" Affichage de la grille de l'adversaire 3 \n\n");
					afficher_matrice_pion(mat3);
				}

		case 2 :if(nb_joueur+1!=2){
					printf(" Affichage de la grille de l'adversaire 2 \n\n");
					afficher_matrice_pion(mat2);
				}
				if(nb_joueur+1!=1){
					printf(" Affichage de la grille de l'adversaire 1 \n\n");
					afficher_matrice_pion(mat);
				}
		default : break;
	}
   if(nb_joueur+1==1){
      mat_case=creer_matrice_joueur( mat.nbl, mat.nbc );
      init_matrice_joueur(mat_case);
      nb_bat=choixbateau(batjoueur1, mat_case);
      send(client_fd, &mat_case.nbc, sizeof(mat_case.nbc), 0);
      send(client_fd, &mat_case.nbl, sizeof(mat_case.nbl), 0);
      send(client_fd, mat_case.grille[0], sizeof(case_t)*mat_case.nbl*mat_case.nbc, 0);
      send(client_fd, &nb_bat, sizeof(int), 0);
      for(en_tete(&batjoueur1); !hors_liste(&batjoueur1); suivant(&batjoueur1)){
        valeur_elt(&batjoueur1, &bat);
        send(client_fd, &bat.type, sizeof(type_t), 0);
        send(client_fd, &bat.coord.x, sizeof(int), 0);
        send(client_fd, &bat.coord.y, sizeof(int), 0);
        send(client_fd, &bat.taille, sizeof(int), 0);
        send(client_fd, &bat.dir, sizeof(dir_t), 0);
        send(client_fd, &bat.etat, sizeof(etat_t), 0);
        send(client_fd, &bat.nb_touche, sizeof(int), 0);
      }

      }else{
        switch(nb_cli){
      		case 5 :
                    mat_case5=creer_matrice_joueur( mat5.nbl, mat5.nbc );
                    init_matrice_joueur(mat_case5);
                    init_liste(&batjoueur5);
                    recv(client_fd, &mat_case5.nbc, sizeof(mat_case5.nbc), 0);
                    recv(client_fd, &mat_case5.nbl, sizeof(mat_case5.nbl), 0);
                    recv(client_fd, mat_case5.grille[0], sizeof(case_t)*mat_case5.nbl*mat_case5.nbc, 0);
                    recv(client_fd, &nb_bat, sizeof(int), 0);


                  for(int i=0; i<nb_bat; i++){
                     recv(client_fd, &bat.type, sizeof(type_t), 0);
                     recv(client_fd, &bat.coord.x, sizeof(int), 0);
                     recv(client_fd, &bat.coord.y, sizeof(int), 0);
                     recv(client_fd, &bat.taille, sizeof(int), 0);
                     recv(client_fd, &bat.dir, sizeof(dir_t), 0);
                    recv(client_fd, &bat.etat, sizeof(etat_t), 0);
                     recv(client_fd, &bat.nb_touche, sizeof(int), 0);
                     placement_bateau(batjoueur_np, &bat, bat.dir, bat.coord, mat_case5);
                   }
                   init_matrice_joueur(mat_case5);
                   placer_bateau(batjoueur_np, batjoueur5, mat_case5);
                   break;


      		case 4 :

                mat_case4=creer_matrice_joueur( mat4.nbl, mat4.nbc );
                init_matrice_joueur(mat_case4);
                init_liste(&batjoueur4);
                recv(client_fd, &mat_case4.nbc, sizeof(mat_case4.nbc), 0);
                recv(client_fd, &mat_case4.nbl, sizeof(mat_case4.nbl), 0);
                recv(client_fd, mat_case4.grille[0], sizeof(case_t)*mat_case4.nbl*mat_case4.nbc, 0);
                recv(client_fd, &nb_bat, sizeof(int), 0);
                for(int i=0; i<nb_bat; i++){
                   recv(client_fd, &bat.type, sizeof(type_t), 0);
                   recv(client_fd, &bat.coord.x, sizeof(int), 0);
                   recv(client_fd, &bat.coord.y, sizeof(int), 0);
                   recv(client_fd, &bat.taille, sizeof(int), 0);
                   recv(client_fd, &bat.dir, sizeof(dir_t), 0);
                   recv(client_fd, &bat.etat, sizeof(etat_t), 0);
                   recv(client_fd, &bat.nb_touche, sizeof(int), 0);
                   placement_bateau(batjoueur_np, &bat, bat.dir, bat.coord, mat_case4);
                 }
                 init_matrice_joueur(mat_case4);
                 placer_bateau(batjoueur_np, batjoueur4, mat_case4);
                break;

      		case 3 :
              mat_case3=creer_matrice_joueur( mat3.nbl, mat3.nbc );
              init_matrice_joueur(mat_case3);
              init_liste(&batjoueur3);
              recv(client_fd, &mat_case3.nbc, sizeof(mat_case3.nbc), 0);
              recv(client_fd, &mat_case3.nbl, sizeof(mat_case3.nbl), 0);
              recv(client_fd, mat_case3.grille[0], sizeof(case_t)*mat_case3.nbl*mat_case3.nbc, 0);
              recv(client_fd, &nb_bat, sizeof(int), 0);
              for(int i=0; i<nb_bat; i++){
                 recv(client_fd, &bat.type, sizeof(type_t), 0);
                 recv(client_fd, &bat.coord.x, sizeof(int), 0);
                 recv(client_fd, &bat.coord.y, sizeof(int), 0);
                 recv(client_fd, &bat.taille, sizeof(int), 0);
                 recv(client_fd, &bat.dir, sizeof(dir_t), 0);
                 recv(client_fd, &bat.etat, sizeof(etat_t), 0);
                 recv(client_fd, &bat.nb_touche, sizeof(int), 0);
                 placement_bateau(batjoueur_np, &bat, bat.dir, bat.coord, mat_case3);
               }
               init_matrice_joueur(mat_case3);
               placer_bateau(batjoueur_np, batjoueur3, mat_case3);
               break;

      		case 2 :
              mat_case2=creer_matrice_joueur( mat2.nbl, mat2.nbc );
              init_matrice_joueur(mat_case2);
              init_liste(&batjoueur2);
              recv(client_fd, &mat_case2.nbc, sizeof(mat_case2.nbc), 0);
              recv(client_fd, &mat_case2.nbl, sizeof(mat_case2.nbl), 0);
              recv(client_fd, mat_case2.grille[0], sizeof(case_t)*mat_case2.nbl*mat_case2.nbc, 0);
              recv(client_fd, &nb_bat, sizeof(int), 0);
              for(int i=0; i<nb_bat; i++){
                 recv(client_fd, &bat.type, sizeof(type_t), 0);
                 recv(client_fd, &bat.coord.x, sizeof(int), 0);
                 recv(client_fd, &bat.coord.y, sizeof(int), 0);
                 recv(client_fd, &bat.taille, sizeof(int), 0);
                 recv(client_fd, &bat.dir, sizeof(dir_t), 0);
                 recv(client_fd, &bat.etat, sizeof(etat_t), 0);
                 recv(client_fd, &bat.nb_touche, sizeof(int), 0);
                 placement_bateau(batjoueur_np, &bat, bat.dir, bat.coord, mat_case2);
               }
               affichage_flotte(batjoueur_np,mat_case2);
               init_matrice_joueur(mat_case2);
               placer_bateau(batjoueur_np, batjoueur2, mat_case2);
               affichage_flotte(batjoueur2,mat_case2);


              break;

      		default : break;
      	}

      }

    if(nb_joueur+1!=1){
          send(client_fd, &ok, sizeof(int), 0);
    }
    if(nb_joueur+1!=1){
      switch(nb_cli){
          case 5 :
                    send(client_fd, &mat_case5.nbc, sizeof(mat_case5.nbc), 0);
                    send(client_fd, &mat_case5.nbl, sizeof(mat_case5.nbl), 0);
                    send(client_fd, mat_case5.grille[0], sizeof(case_t)*mat_case5.nbl*mat_case5.nbc, 0);
                    send(client_fd, &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur5); !hors_liste(&batjoueur5); suivant(&batjoueur5)){
                      valeur_elt(&batjoueur5, &bat);
                      send(client_fd, &bat.type, sizeof(type_t), 0);
                      send(client_fd, &bat.coord.x, sizeof(int), 0);
                      send(client_fd, &bat.coord.y, sizeof(int), 0);
                      send(client_fd, &bat.taille, sizeof(int), 0);
                      send(client_fd, &bat.dir, sizeof(dir_t), 0);
                      send(client_fd, &bat.etat, sizeof(etat_t), 0);
                      send(client_fd, &bat.nb_touche, sizeof(int), 0);
                    }

          case 4 :
                    send(client_fd, &mat_case4.nbc, sizeof(mat_case4.nbc), 0);
                    send(client_fd, &mat_case4.nbl, sizeof(mat_case4.nbl), 0);
                    send(client_fd, mat_case4.grille[0], sizeof(case_t)*mat_case4.nbl*mat_case4.nbc, 0);
                    send(client_fd, &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur4); !hors_liste(&batjoueur4); suivant(&batjoueur4)){
                      valeur_elt(&batjoueur4, &bat);
                      send(client_fd, &bat.type, sizeof(type_t), 0);
                      send(client_fd, &bat.coord.x, sizeof(int), 0);
                      send(client_fd, &bat.coord.y, sizeof(int), 0);
                      send(client_fd, &bat.taille, sizeof(int), 0);
                      send(client_fd, &bat.dir, sizeof(dir_t), 0);
                      send(client_fd, &bat.etat, sizeof(etat_t), 0);
                      send(client_fd, &bat.nb_touche, sizeof(int), 0);
                    }

          case 3 :
                    send(client_fd, &mat_case3.nbc, sizeof(mat_case3.nbc), 0);
                    send(client_fd, &mat_case3.nbl, sizeof(mat_case3.nbl), 0);
                    send(client_fd, mat_case3.grille[0], sizeof(case_t)*mat_case3.nbl*mat_case3.nbc, 0);
                    send(client_fd, &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur3); !hors_liste(&batjoueur3); suivant(&batjoueur3)){
                      valeur_elt(&batjoueur3, &bat);
                      send(client_fd, &bat.type, sizeof(type_t), 0);
                      send(client_fd, &bat.coord.x, sizeof(int), 0);
                      send(client_fd, &bat.coord.y, sizeof(int), 0);
                      send(client_fd, &bat.taille, sizeof(int), 0);
                      send(client_fd, &bat.dir, sizeof(dir_t), 0);
                      send(client_fd, &bat.etat, sizeof(etat_t), 0);
                      send(client_fd, &bat.nb_touche, sizeof(int), 0);
                    }

          case 2 :
                    send(client_fd, &mat_case2.nbc, sizeof(mat_case2.nbc), 0);
                    send(client_fd, &mat_case2.nbl, sizeof(mat_case2.nbl), 0);
                    send(client_fd, mat_case2.grille[0], sizeof(case_t)*mat_case2.nbl*mat_case2.nbc, 0);
                    send(client_fd, &nb_bat, sizeof(int), 0);
                    for(en_tete(&batjoueur2); !hors_liste(&batjoueur2); suivant(&batjoueur2)){
                      valeur_elt(&batjoueur2, &bat);
                      send(client_fd, &bat.type, sizeof(type_t), 0);
                      send(client_fd, &bat.coord.x, sizeof(int), 0);
                      send(client_fd, &bat.coord.y, sizeof(int), 0);
                      send(client_fd, &bat.taille, sizeof(int), 0);
                      send(client_fd, &bat.dir, sizeof(dir_t), 0);
                      send(client_fd, &bat.etat, sizeof(etat_t), 0);
                      send(client_fd, &bat.nb_touche, sizeof(int), 0);
                    }


              break;

          default : break;
      }
    }


    if(nb_joueur+1!=1){
          send(client_fd, &ok, sizeof(int), 0);
    }



  	while (1){
		recv(client_fd, &tour_atk, sizeof(tour_atk), 0);
		printf("\n \n ----------------------------------------------------------------------------- \n");
		printf(" Tour de  %i \n", tour_atk);
		if(tour_atk==nb_joueur+1){
      if(nb_cli!=2){
          printf("Le nombre de joueurs est de %i",nb_cli);
        do{
        	printf("\n Qui voulez-vous attaquer ? ");
  			scanf("%i", &choix_j_atk);
  			if(choix_j_atk<1 || choix_j_atk>nb_cli){
  				printf("Le numéro du joueur est inexistant. Veuillez entrer un numéro de joueur compris entre 1 et %d \n", nb_cli );
  			}
        if(choix_j_atk== nb_joueur+1){
          printf("Vous ne pouvez vous attaquer vous-même !\n");
        }
  		}while(choix_j_atk<1 || choix_j_atk>nb_cli || choix_j_atk==nb_joueur+1);
        send(client_fd, &choix_j_atk, sizeof(choix_j_atk), 0);
      }

          if(nb_joueur+1!=tour_atk){
          send(client_fd, &ok, sizeof(int), 0);
    }

      do{
				printf("\n Quelle case voulez-vous attaquer ( de la forme \"ligne colonne\")? ");
				scanf("%i %i", &choix_c_atk, &choix_c_atk2);
				if(choix_c_atk<=0 || choix_c_atk2<=0 || choix_c_atk>mat.nbl || choix_c_atk2>mat.nbc){
					printf("Cette case n'est pas dans la grille\n");
				}
				if( choix_c_atk>0 && choix_c_atk2>0 && choix_c_atk<=mat.nbl && choix_c_atk2<=mat.nbc && mat.grille[choix_c_atk-1][choix_c_atk2-1].c!= AUCUNE){
					printf("Cette case à déjà été selectionnée !");
				}
			}while( choix_c_atk<=0 || choix_c_atk2<=0 || choix_c_atk>mat.nbl || choix_c_atk2>mat.nbc || mat.grille[choix_c_atk-1][choix_c_atk2-1].c!= AUCUNE);

			send(client_fd, &choix_c_atk, sizeof(choix_c_atk), 0);
			send(client_fd, &choix_c_atk2, sizeof(choix_c_atk2), 0);
			printf("\n Envoyé \n");
			printf(" ----------------------------------------------------------------------------- \n \n");
		}
		else{
			recv(client_fd, &info_j_atk, sizeof(info_j_atk), 0);
			recv(client_fd, &info_c_atk, sizeof(info_c_atk), 0);
			recv(client_fd, &info_c_atk2, sizeof(info_c_atk2), 0);

			if( info_j_atk == nb_joueur+1){
				printf("\n Le joueur %i vous attaque en case n° %i %i\n", tour_atk, info_c_atk, info_c_atk2);

			}else{
				printf("\n Le joueur %i attaque le joueur %i en case n° %i %i\n", tour_atk, info_j_atk, info_c_atk, info_c_atk2);
			}
			printf(" ----------------------------------------------------------------------------- \n \n");
		}

	}
}
