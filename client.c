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
#include 	<fcntl.h>
#include 	"c_util.h"

#define MAX_BUF_LENGTH 4096

int main(int argc, char *argv[]) {
	int	socket_fd, send_len, recv_len;
	//int from_size;
	struct sockaddr_in	dest, from_serv;
	struct hostent *gethostbyname(), *hostptr;
	socklen_t fsize = sizeof(from_serv);


	// where socketfd is the socket you want to make non-blocking
	//int status = fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK);

	//if (status == -1){
	  //perror("calling fcntl");
	  // handle the error.  By the way, I've never seen fcntl fail in this way
	//}

//	fprintf( stdout, "RECV_UDP Local socket is: \n");
//	printf ("  family %d, addr %s, port %d\n", dest.sin_family,
//			inet_ntoa(dest.sin_addr), ntohs((unsigned short)(dest.sin_port)));
//	fflush(stdout);

	while ( 1 ) {
		memset(&message_buf, 0, sizeof(message_buf));
		fprintf(stdout, "flop: ");

		char input[50], command[50], arg[50];
		fgets(input, 50, stdin); //read line
		sscanf(input, "%s", command); //separate out first arg, consider using strtok() instead of sscanf()

		if (strcmp("quit", command) == 0) {
			fprintf(stdout, "\n Exiting the floppy disk shell... \n");
			close(socket_fd);
			return EXIT_SUCCESS;
		} else if (strcmp("help", command) == 0) {
			help();
			continue;
		} else if (strcmp("fmount", command) == 0) {
			sscanf(input, "%s %s", command, arg);

			socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
			if (socket_fd == -1) {
				perror ("send_udp:socket");
				exit(1);
			}

			memset(&dest, 0, sizeof(dest));                /* zero the struct */
			if ((hostptr = gethostbyname(arg)) == NULL){
				fprintf(stderr, "send_udp: invalid host name, %s\n",argv[1]);
				exit(1);
			}

			dest.sin_family = AF_INET;
			bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
			dest.sin_port = htons((u_short)0x3333);

			strcpy(message_buf.cmd, command);

			send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
			if (send_len < 0) {
				perror("There was an error, please make sure the floppy is mounted. ");
				exit(1);
			}
		} else if (strcmp("fumount", command) == 0) {
			sscanf(input, "%s %s", command, arg);

			memset(&dest, 0, sizeof(dest));                /* zero the struct */
			if ((hostptr = gethostbyname(arg)) == NULL){
				fprintf(stderr, "send_udp: invalid host name, %s\n",argv[1]);
				exit(1);
			}

			dest.sin_family = AF_INET;
			bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
			dest.sin_port = htons((u_short)0x3333);

			strcpy(message_buf.cmd, command);

			send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
			if (send_len < 0) {
				perror("There was an error, please make sure the floppy is mounted. ");
				exit(1);
			}
		} else if (strcmp("showsector", command) == 0) {
			sscanf(input, "%s %s", command, arg);

			message_buf.sector_number = atoi(arg);
			strcpy(message_buf.cmd, command);

			send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
			if (send_len < 0) {
				perror("There was an error, please make sure the floppy is mounted. ");
				exit(1);
			}
		} else if (strcmp("structure", command) == 0) {
			sscanf(input, "%s %s", command, arg);

			message_buf.sector_number = 0;
			strcpy(message_buf.cmd, command);

			send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
			if (send_len < 0) {
				perror("There was an error, please make sure the floppy is mounted. ");
				exit(1);
			}
		} else if(strcmp("traverse", command) == 0) {
			if (strstr(input, "-l") == NULL) {
				traverse(command);
			} else if (strstr(input, "-l") != NULL) {
				sscanf(input, "%s %s", command, arg);
				traverse(arg);
			}
			else {
				printf("Error invalid argument, please try again! \n");
				continue;
			}
		} else {
			fprintf(stdout, "Invalid command, please try again.\n");
			continue;
		}

		memset(&message_buf, 0, sizeof(message_buf));

		recv_len = recvfrom(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&from_serv, &fsize);

		/*do {
			recv_len = recvfrom(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&from_serv, &fsize);

			if (recv_len == -1) {
				fprintf(stdout, "There was an error");
			} else {
				rcv_data += message_buf.data;
			}
		} while ( recv_len >= MAX_BUF_LENGTH );*/

		if (strcmp("fmount", command) == 0) {
			fprintf(stdout, "%s\n", message_buf.data);
		} else if (strcmp("fumount", command) == 0) {
			close(socket_fd);
			fprintf(stdout, "%s\n", message_buf.data);
		} else if (strcmp("showsector", command) == 0) {
			showsector();
			fflush(stdout);
		} else if (strcmp("structure", command) == 0) {
			structure();
			fflush(stdout);
		} else if(strcmp("traverse", command) == 0) {
			if (strstr(input, "-l") == NULL) {
				traverse(command);
				fflush(stdout);
			} else if (strstr(input, "-l") != NULL) {
				sscanf(input, "%s %s", command, arg);
				traverse(arg);
				fflush(stdout);
			}
			else {
				printf("Error invalid argument, please try again! \n");
				fflush(stdout);
				continue;
			}
		}
	}

	return 0;
}
