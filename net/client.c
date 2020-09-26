/* Fichier: client.c
 * Description:
 *  Programme principal du client.
 *  Se connecte au server.
 *
 *  Utilisation: ./client address
 *  Exemple: ./client localhost
 *  		 ./client 192.168.0.1
 *
 *  Compiler avec gcc -D CLIENT
 *
 * Auteurs:
 * 	Guillaume Bergeron
 * 	Brandon Cote
 * 	Emile Forcier
 * 	Laurent Tremblay
 *
 * Date: 31-03-2020
 */
#include <arpa/inet.h>	 // INET_ATON
#include <netdb.h>		 //HOSTEN
#include <netinet/in.h>  //SOCKADDR_IN
#include <sys/socket.h>	 // SOCKET and ACCEPT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_SIZE 32
#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 1234

int main(int argc, char ** argv) {

	if (argc != 2) {
		fprintf(stderr, "only a single argument is supported\n");
		return 1;
	}

	int client_sock;
	struct hostent * host;
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

	if (!inet_aton(argv[1],&server_addr.sin_addr)){
		host = gethostbyname(argv[1]);
		memcpy(&server_addr.sin_addr,host->h_addr,sizeof(server_addr.sin_addr));
	}


	if (!host) {
		herror("error looking up host");
		exit(1);
	}

	enum state{
		CHECK_COMMAND,
		CONNECT,
		SEND_COMMAND,
		GET_NRESULT,
		GET_RESULT,
	}client_state = CHECK_COMMAND;

    char cmdbuf[MAX_CMD_SIZE] = { 0 };
    char fbuf[MAX_BUFFER_SIZE] = { 0 };
    int nresult = 0;
	int client_running = 1;
	while(client_running){

		switch(client_state){

		case CHECK_COMMAND:
			printf("Enter a term to search for, q to quit or k to kill :");
			scanf("%s",cmdbuf);

			if(strcmp(cmdbuf,"q") == 0){
				client_running = 0;
			}
			else{
				if ((client_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
					perror("Error creating socket");
					exit(1);
				}
				client_state = CONNECT;
			}

			break;

		case CONNECT:
			if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr))){
				printf("Can't reach server at this moment\n");
				client_state = CHECK_COMMAND;
			}
			else{
				printf("Request sent.\n");
				client_state = SEND_COMMAND;
			}

			break;

		case SEND_COMMAND:
			if(read(client_sock, fbuf, sizeof(fbuf)) > 0){
				if(strcmp(fbuf, "ACK") == 0){
					write(client_sock, cmdbuf, sizeof(cmdbuf));

					if(strcmp(cmdbuf,"k") == 0){
						client_running = 0;
					}
					else{
						client_state = GET_NRESULT;
					}

				}
			}

			break;

		case GET_NRESULT:
			if(read(client_sock,&nresult,sizeof(nresult)) > 0){
				printf("Found %d matching result\n\n",nresult);
				write(client_sock,"ACK",sizeof("ACK"));
				client_state = GET_RESULT;
			}
			break;

		case GET_RESULT:
			if(read(client_sock, fbuf, sizeof(fbuf)) > 0){
				if((strcmp(fbuf,"GOOD BYE") == 0)){
					close(client_sock);
					nresult = 0;
					client_state = CHECK_COMMAND;
				}
				else{
					printf("%s\n",fbuf);
					write(client_sock,"ACK",sizeof("ACK"));
				}
			}
			break;

		}

    }

    return 0;
}
