/*
 * clientUtil.h
 *
 *  Created on: May 2, 2015
 *      Author: Glen
 */
#ifndef C_UTIL_H_
#define C_UTIL_H_

int fd;
unsigned short bytes_per_sector;
unsigned short num_of_sectors;
unsigned short fatbytes;
unsigned short cluster;
char *fat_buffer;
char buf[32];
char recv_buf[6656];

struct {
	char cmd[50];
	char data[512];
	u_long size;
	u_long sector_number;
} message_buf;

void help();
void showsector();
void traverse(char*);
void structure();
void trim(char *);
void print_files(char *, char *, char *);
void print_directories(unsigned short, char *, unsigned short, unsigned short, unsigned short, char *);

#endif /* C_UTIL_H_ */
