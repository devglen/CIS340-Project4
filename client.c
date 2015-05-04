/*
 * client.c
 *
 *  Created on: Apr 28, 2015
 *      Author: Glen
 */
#include	<signal.h>
#include	<errno.h>
#include	<strings.h>
#include	<string.h>
#include 	<stdlib.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include 	<unistd.h>
#include 	<arpa/inet.h>
#include 	<fcntl.h>
#include 	<ctype.h>
#include 	"c_util.h"

int main(int argc, char *argv[]) {
	int	socket_fd, send_len, recv_len;
	struct sockaddr_in	dest, from_serv;
	struct hostent *gethostbyname(), *hostptr;
	socklen_t fsize = sizeof(from_serv);

	while ( 1 ) {
		int standard_receive = 1;
		memset(&message_buf, 0, sizeof(message_buf));
		fprintf(stdout, "flop: ");
		fflush(stdout);

		char input[50], command[50], arg[50];
		fgets(input, 50, stdin); //read command line
		sscanf(input, "%s", command);

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
			message_buf.sector_number = 0;
			strcpy(message_buf.cmd, command);

			send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
			if (send_len < 0) {
				perror("There was an error, please make sure the floppy is mounted. ");
				exit(1);
			}
		} else if(strcmp("traverse", command) == 0) {
			standard_receive = 0;
			if (strstr(input, "-l") == NULL) {

				strcpy(message_buf.cmd, command);

				for (int i = 0; i < 33; i++) {
					message_buf.sector_number = i;
					send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
					if (send_len < 0) {
						perror("There was an error, please make sure the floppy is mounted. ");
						exit(1);
					}

					memset(&message_buf, 0, sizeof(message_buf));

					recv_len = recvfrom(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&from_serv, &fsize);

					if (recv_len < 0) {
						perror("There was an error receiving data from server\n");
					}
					
					fd = open("temp_image", O_WRONLY |  O_CREAT | O_APPEND, 0644);
					if (fd < 0) {
						fprintf(stdout, "ERROR CREATING FILE\n");
					}
					if (write(fd, message_buf.data, message_buf.size) != message_buf.size) {
						write(2, "There was an error writing to temp file\n", 43);
						return -1;
					}

				}
				close(fd);
			} else if (strstr(input, "-l") != NULL) {
				sscanf(input, "%s %s", command, arg);

				strcpy(message_buf.cmd, command);

				for (int i = 0; i < 33; i++) {
					message_buf.sector_number = i;
					send_len = sendto(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&dest, sizeof(dest));
					if (send_len < 0) {
						perror("There was an error, please make sure the floppy is mounted. ");
						exit(1);
					}

					memset(&message_buf, 0, sizeof(message_buf));

					recv_len = recvfrom(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&from_serv, &fsize);

					if (recv_len < 0) {
						perror("There was an error receiving data from server\n");
					}
					
					fd = open("temp_image", O_WRONLY |  O_CREAT | O_APPEND, 0644);
					if (fd < 0) {
						fprintf(stdout, "ERROR CREATING FILE\n");
					}
					if (write(fd, message_buf.data, message_buf.size) != message_buf.size) {
						write(2, "There was an error writing to temp file\n", 43);
						return -1;
					}

				}
				close(fd);
			}
			else {
				printf("Error invalid argument, please try again! \n");
				continue;
			}
		} else {
			fprintf(stdout, "Invalid command, please try again.\n");
			continue;
		}

		if (standard_receive) {
			memset(&message_buf, 0, sizeof(message_buf));

			recv_len = recvfrom(socket_fd, &message_buf, sizeof(message_buf), 0, (struct sockaddr *)&from_serv, &fsize);
			
			if (recv_len < 0) {
				perror("There was an error receiving data from server\n");
			}		
		}

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
