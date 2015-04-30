/*
 * client.c
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
#include 	<unistd.h>
#include 	<arpa/inet.h>

int main(int argc, char *argv[]) {
	int	socket_fd, send_len, recv_len, from_size;
	struct sockaddr_in	dest, from_serv;
	struct hostent *gethostbyname(), *hostptr;

	struct {
		char cmd[50];
		char data[512];
		u_long sector_number;
	} message_buf;

	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	if (socket_fd == -1) {
		perror ("send_udp:socket");
		exit(1);
	}

	memset(&dest, 0, sizeof(dest));                /* zero the struct */
	if ((hostptr = gethostbyname(argv[1])) == NULL){
		fprintf(stderr, "send_udp: invalid host name, %s\n",argv[1]);
		exit(1);
	}

	dest.sin_family = AF_INET;
	bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
	dest.sin_port = htons((u_short)0x3333);

	fprintf( stdout, "RECV_UDP Local socket is: \n");
	printf ("  family %d, addr %s, port %d\n", dest.sin_family,
			inet_ntoa(dest.sin_addr), ntohs((unsigned short)(dest.sin_port)));
	fflush(stdout);

	char kill[5] = "DDDD\0";
	while ( 1 ) {
		char x[50];
		printf("What would you like to do? ");
		scanf("%s",x);
		printf("sent this to server: %s\n", x);


		if(strcmp(kill, x) == 0){
		   fprintf(stdout, "entered: %s\n", x);
		   close(socket_fd);
		   break;
		}

		strcpy(message_buf.cmd, x);
		message_buf.sector_number = htonl(10);
		strcpy(message_buf.data, "<>");

		send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
		if (send_len < 0) {
			perror("send_udp:sendto");
			exit(1);
		}

		printf("After send\n");

		from_size = sizeof(from_serv);
		recv_len = recv(socket_fd, &message_buf, sizeof(message_buf), 0);

		fprintf(stdout, "Received new data: %s, (%d bytes).\n", message_buf.data, recv_len);
	}

	return 0;

}
