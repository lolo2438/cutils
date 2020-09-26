/* Fichier: net.h
 * Description:
 *	Interface du module pour la création et
 *	la gestion des connections par socket.
 *
 * Auteurs:
 * 	Guillaume Bergeron
 * 	Brandon Cote
 * 	Emile Forcier
 * 	Laurent Tremblay
 *
 * Date: 31-03-2020
 */
#ifndef __NET_H__
#define __NET_H__

/* Function net_start
 *
 * Desc: Starts the network interface
 *
 * Out: 0 : Success
 *     -1 :Failed creating socket
 *     -2 :Failed settings socket
 *     -3 :Failed binding socket
 *     -4 :Failed listening on socket
 *
 * Spec: Only call this function once if it succeeded.
 *
 */
int net_start(void);

/* Function net_receive
 *
 * Desc: This function checks if a client connected to the server and
 * 		 return its file descriptor.
 *
 * Out: The file descriptor of the client socket
 * 		-1 : No client connected
 *
 * Usage: if(client_sock = net_receive()){
 * 				do stuff..
 *
 * Spec: This function does NOT block the thread
 */
int net_receive(void);

/* Function net_close
 *
 * Desc: Closes the socket in argument
 * 		 If the socket value is 0, it closes
 * 		 the server socket
 *
 * Out: The return value is the same of the linux close function
 */
int net_close(int socket);

#endif
