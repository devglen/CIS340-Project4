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
#include    	<fcntl.h>
#include 	"utility.h"

#define 	MAX_DATA_LENGTH 512


int main(int argc, char *argv[]) {
	// mount the floppy on execution
	if (argc > 1) {
		fmount(argv[1]);
	} else {
		fprintf(stdout, "Please provide an imagefile to mount.\n");
		exit(1);
	}
	struct sockaddr_in serv, from_serv; /* socket info about our server */
	int socket_fd, recv_len;            /* socket used to listen for incoming connections */
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

	while( 1 ) {
		memset(&message, 0, sizeof(message));
		recv_len = recvfrom(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, &socksize);
		if (recv_len < 0)
			perror("Error Receiving data packet from client\n");

		if(recv_len > 0){
			printf("Incoming connection from %s \n", inet_ntoa(from_serv.sin_addr));

			if (strcmp("fmount", message.cmd) == 0) {
				if (fd > -1) {
					strcpy(message.data, "Floppy mounted successfully.");
					message.size = sizeof("Floppy mounted successfully.");
				} else {
					strcpy(message.data, "There was a problem mounting the floppy.");
					message.size = sizeof("There was a problem mounting the floppy.");
				}
				sendto(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, sizeof(from_serv));
			} else if (strcmp("fumount", message.cmd) == 0) {
				strcpy(message.data, "Floppy has been unmounted successfully.");
				message.size = sizeof("Floppy has been unmounted successfully.");
				sendto(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, sizeof(from_serv));
			} else {
				get_sector_data(message.sector_number);
				memcpy(message.data, buf, message.size);

				sendto(socket_fd, &message, sizeof(message), 0, (struct sockaddr *)&from_serv, sizeof(from_serv));
			}

		} else {
			consocket = accept(socket_fd, (struct sockaddr *)&from_serv, &socksize);
		}
	}
	return 0;
}
