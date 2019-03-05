#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 32000
void tcp_connection_server(int * server_fd, int * client_fd)
{
    struct sockaddr_in server_addr, client_addr;    
    int client_addr_len, port_no=PORT;


    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);


    while( bind(*server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
    {

        server_addr.sin_port = htons(port_no);
    }

    printf("\n -- EN ATTENTE --\n");

  
 
    printf("Host IP: %s", INADDR_ANY); 


    if( listen(*server_fd, 5) < 0)
    {
        perror("Erorr in Listen()\n");
        exit(0);
    }

    client_addr_len = sizeof(client_addr);

    *client_fd = accept(*server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if(*client_fd < 0)
    {
        perror("Error in accept()\n");
        exit(0);
    }

    printf(" -- 1 CLIENT CONNNECTE --\n");

}

int main(){

int server_fd, client_fd;

   	tcp_connection_server(&server_fd, &client_fd);
	int reponse=1;
	int question;

	while(1==1){
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
