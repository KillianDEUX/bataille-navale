#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#define PORT 32000
void tcp_connection_client(int * client_fd)
{
    struct sockaddr_in serv_addr;
    int port_no=PORT;



    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(port_no);


    if( connect(*client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connexion impossible, verifiez que le serveur est démarré ! \n");
        exit(0);
    }
    printf(" -- CONNECTE -- \n");
}

int main() {
    int reponse=1;		
    int question;
    int server_fd, client_fd;
    
    tcp_connection_client(&client_fd);

		
		printf("A mon tour, quelle case voulez-vous attaquer ? ");
		scanf("%i", &question);
		send(client_fd, &question, sizeof(question), 0);
		while (1==1){
		
		recv(client_fd, &reponse, sizeof(reponse), 0);
	

		while (reponse!=0){

			printf(" AIE ! - j'ai mal à la case : \n %i \n \n", reponse);
			reponse=0;
			printf("A mon tour, quelle case voulez-vous attaquer ? ");
			scanf("%i", &question);
			send(client_fd, &question, sizeof(question), 0);
			printf("\n");

		
		}
	}
}
