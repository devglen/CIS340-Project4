/*
 * utilility.h
 *
 *  Created on: May 2, 2015
 *      Author: Glen
 */

#ifndef UTILITY_H_
#define UTILITY_H_


struct {
	char cmd[50];
	char data[512];
	u_long size;
	u_long sector_number;
} message;

int fd;
unsigned short bytes_per_sector;
unsigned short num_of_sectors;
unsigned short fatbytes;
unsigned short cluster;
char *fat_buffer;
char *buf;

void fmount(char*);
void get_sector_data(u_long);

#endif /* UTILITY_H_ */
