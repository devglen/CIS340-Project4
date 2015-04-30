/*
 * server.c
 *
 *  Created on: Apr 28, 2015
 *      Author: Glen
 */
#include	<signal.h>
#include	<errno.h>
#include	<strings.h>
#include 	<stdlib.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include 	<arpa/inet.h>
#include 	"util.h"

int main(int argc, char *argv[]) {
	struct sockaddr_in dest; /* socket info about the machine connecting to us */
	struct sockaddr_in serv, from_serv; /* socket info about our server */
	int socket_fd, from_size, recv_len;            /* socket used to listen for incoming connections */
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv));           /* zero the struct before filling the fields */
	serv.sin_family = (short)AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
	serv.sin_port = htons((u_short)0x3333);
	fprintf( stdout, "RECV_UDP Local socket is: \n");
	printf ("  family %d, addr %s, port %d\n", serv.sin_family,
		    inet_ntoa(serv.sin_addr), ntohs((unsigned short)(serv.sin_port)));
	fflush(stdout);

	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0) {
		perror ("recv_udp:socket");
		exit (1);
	}

	if (bind(socket_fd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
		perror("recv_udp:bind");
		exit(1);
	}

	listen(socket_fd, 1);

	int consocket = accept(socket_fd, (struct sockaddr *)&from_serv, &socksize);

	//fprintf(stdout, "Waiting for Connection Request... \n");
	char kill[5] = "KKKK\0";
	while( 1 ) {
		recv_len = recvfrom(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, &socksize);
		if (recv_len < 0)
			perror("recv_udp:recvfrom");
		fprintf(stdout, "recv_udp: %d, Packet from:", &from_serv);
		fprintf(stdout, "Got data ::%s%d%c\n",message.cmd,ntohl(message.data),ntohl(message.sector_number));
		fflush(stdout);

		if(strcmp(kill, message.cmd) == 0){
			printf("entered the kill word: %s\n", message.cmd);
			close(consocket);
			close(socket_fd);
			return EXIT_SUCCESS;
		}

		if(recv_len > 0){
			printf("\n RECIEVED DATA = %lu \n" , sizeof(message));
			printf("Command received is: %s\n", message.cmd);
			printf("Incoming connection from %s - sending reversed message\n", inet_ntoa(from_serv.sin_addr));

			strcpy(message.data, "<NEW DATA>");

			sendto(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, sizeof(from_serv));
		} else {
			consocket = accept(socket_fd, (struct sockaddr *)&from_serv, &socksize);
		}
	}
	return 0;
}
