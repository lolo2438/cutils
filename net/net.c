/* Fichier: net.c
 * Description:
 *	Implementation du module pour la création et
 *	la gestion des connections par socket.
 *
 * Auteurs:
 * 	Guillaume Bergeron
 * 	Brandon Cote
 * 	Emile Forcier
 * 	Laurent Tremblay
 *
 * Date: 31-03-2020
 *
 * More info: IP(7) : http://man7.org/linux/man-pages/man7/ip.7.html
 */
#include <sys/types.h> //Compatibility
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "net.h"

#define SERVER_PORT 1234

static int g_socket = 0;

static struct sockaddr_in g_addr = { 0 };


int net_start(void){

	 if(g_socket){
		 return 0;
	 }

	 if ((g_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		 perror("Failed creating socket");
		 return -1;
	 }

	 /* http://www.unixguide.net/network/socketfaq/4.5.shtml */
	 int enable = 1;
	 if(setsockopt(g_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable))){
		 perror("Failed settings socket");
		 return -2;
	 }

	 /* Make socket non blocking, important for threads to work */
	 int flags = fcntl(g_socket, F_GETFL, 0);
	 fcntl(g_socket,F_SETFL, flags | O_NONBLOCK);

	 memset(&g_addr.sin_addr, 0, sizeof(g_addr.sin_addr));
	 g_addr.sin_family = AF_INET;
	 g_addr.sin_port = htons(SERVER_PORT);


	 if(bind(g_socket,(struct sockaddr *) &g_addr, sizeof(g_addr))){
		 perror("Failed binding socket");
		 return -3;
	 }

	 if(listen(g_socket,5)){
		 perror("Failed listening on socket");
		 return -4;
	 }

	return 0;
}

int net_receive(void){

	socklen_t server_addr = sizeof(g_addr);
	int client_sock;

	if((client_sock = accept(g_socket, (struct sockaddr *) &g_addr, &server_addr)) == -1 ){
		return 0;
	}

	/* Clear the NONBLOCK flag from inherited from server socket */
	int flags = fcntl(client_sock, F_GETFL, 0);
	fcntl(g_socket,F_SETFL, flags | ~O_NONBLOCK);

	return client_sock;
}


int net_close(int socket){

	return close(socket = 0 ? g_socket : socket);
}
