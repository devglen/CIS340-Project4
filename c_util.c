/*
 * clientUtil.c
 *
 *  Created on: May 2, 2015
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
#include    	<arpa/inet.h>
#include    	<fcntl.h>
#include    	<string.h>
#include    	<unistd.h>
#include    	<sys/wait.h>
#include 	<ctype.h>
#include 	"c_util.h"

void help() {
    fprintf(stdout, "The available commands are:\n");
    fprintf(stdout, "    help                    - display a list of available commands.\n");
    fprintf(stdout, "    fmount <hostname>      	- mount the specified image file\n");
    fprintf(stdout, "    fumount <hostname>      - umount the mounted floppy disk. \n");
    fprintf(stdout, "    structure               - list the structure of the floppy disk image.\n");
    fprintf(stdout, "    traverse [-l]           - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.\n");
    fprintf(stdout, "    showsector <sector_num> - show the content of the given sector.\n");
    fprintf(stdout, "    quit                    - quit the floppy shell \n");
}

void showsector() {
    char* buf = (char*)message_buf.data;
    int i;

    fprintf(stdout, "hex dump of sector : %d\n", (int)message_buf.sector_number);
    fprintf(stdout, "%5s", " ");

    for (i=0;i<16;i++)
        fprintf(stdout, "%5x", i);

    fprintf(stdout, "\n");

    for (i=0; i < message_buf.size; i++) {
            if (!(i%16)) {
                fprintf(stdout, "\n");
                fprintf(stdout, "%5x", i);
            }
            fprintf(stdout, "%5x", buf[i]&0xff);
    }

    fprintf(stdout, "\n");
}

void structure() {
    char* buf = (char*)message_buf.data;

    unsigned short lowbyte, highbyte;
    unsigned short nbytesec; 	/* the number of bytes per sector */
    unsigned short nsector;	/* the number of sectors per cluster */
    unsigned short nFAT;	/* the number of FAT */
    unsigned short rentry;	/* the number of entries in the root directory */
    unsigned short nsecfat; /* the number of sectors used by FAT */
    int i = 0;

    lowbyte = ((unsigned short) buf[11]) & 0xff;
    highbyte = ((unsigned short) buf[12]) & 0xff;
    nbytesec = lowbyte | (highbyte << 8);				/* get the number of bytes per sector */
    nsector = ((unsigned short) buf[13]) & 0xff;			/* get the number of sectors per cluster */
    nFAT = ((unsigned short) buf[16]) & 0xff;			/* get the number of FAT table */
    lowbyte = ((unsigned short) buf[17]) & 0xff;
    highbyte = ((unsigned short) buf[18]) & 0xff;
    rentry = lowbyte | (highbyte << 8);				/* get the number of root entries */
    lowbyte = ((unsigned short) buf[19]) & 0xff;
    highbyte = ((unsigned short) buf[20]) & 0xff;			/* get the number of logical sectors */
    lowbyte = ((unsigned short) buf[22]) & 0xff;
    highbyte = ((unsigned short) buf[23]) & 0xff;
    nsecfat = lowbyte | (highbyte << 8);				/* get the number of sectors used by FAT */

    fprintf(stdout, "\t\tnumber of FAT:\t\t\t%5d\n", nFAT);
    fprintf(stdout, "\t\tnumber of sectors used by FAT:\t%5d\n", nsecfat);
    fprintf(stdout, "\t\tnumber of sectors per cluster:\t%5d\n", nsector);
    fprintf(stdout, "\t\tnumber of ROOT Entries:\t\t%5d\n", rentry);
    fprintf(stdout, "\t\tnumber of bytes per sector:\t%5d\n", nbytesec);
    fprintf(stdout, "\t\t---Sector #---     ---Sector Types---\n");
    fprintf(stdout, "\t\t      0                  BOOT       \n");

	for (i=0;i<nFAT;i++)
		fprintf(stdout, "\t\t%5.2d -- %-15.2d FAT%-10d\n", nsecfat*i+1, nsecfat*(i+1), i+1);
	fprintf(stdout, "\t\t%5.2d -- %-15.2d ROOT DIRECTORY\n", 1+nFAT*nsecfat, rentry*32/nbytesec+nFAT*nsecfat);
	fprintf(stdout, "\n");
}

void print_directories(unsigned short cluster, char *directory,
		unsigned short filebytes, unsigned short num_of_sectors,
		unsigned short bytes_per_sector, char *flag) {
	char buf[32], dirname[9], adir[256], ext[4];
	unsigned short new_cluster, low, high;
	unsigned ptr;
	int counter = 0;

	ptr = (filebytes + (cluster - 2)*num_of_sectors)*bytes_per_sector;
	strcpy(adir, directory);
	if ((lseek(fd, ptr, 0)) != ptr) {
		printf("Error setting the file pointer to beginning\n");
		exit(1);
	}

	int bytesread;
	if ( ( bytesread = read(fd, buf, sizeof(buf)) ) < 0) {
		printf("Error reading file entry\n");
		exit(1);
	}

	while (buf[0] != 0x0) {
		if (counter++ >= num_of_sectors*bytes_per_sector/32) {
			if (cluster%2) {
					low = (((unsigned short) fat_buffer[(3*cluster - 1)/2])>>4) & 0x000f;
					high = (((unsigned short) fat_buffer[(3*cluster + 1)/2])<<4) & 0x0ff0;
			}else {
					low = ((unsigned short) fat_buffer[3*cluster/2]) & 0x00ff;
					high = (((unsigned short) fat_buffer[(3*cluster + 2)/2])<<8) & 0x0f00;
			}
			cluster = low | high;
			if (cluster == 0x0 || cluster > 0xff0) {
				break;
			}
			else {
				counter = 0;
				ptr = (filebytes + (cluster - 2)*num_of_sectors)*bytes_per_sector;
				if ((lseek(fd, ptr, 0)) != ptr) {
					printf("There was a problem moving the pointer \n");
					exit(1);
				}
				if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
					printf("Error reading file entry\n");
					exit(1);
				}
				continue;
			}
		}

		// exclude free space and removed files
		if (isprint((unsigned short) (buf[0] & 0xff))
				&& (unsigned short) (buf[0] & 0xff) != 0xe5
				&& (unsigned short) (buf[11]&0x08) != 0x08) {
			print_files(buf, directory, flag);
			if (buf[11]&0x10) {
				new_cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
				strncpy(dirname, buf, 8);
				strncpy(ext, buf+8, 3);
				dirname[8] = '\0';
				ext[3] = '\0';
				trim(dirname);
				trim(ext);
				if (strcmp(dirname, ".") && strcmp(dirname, "..")) {
					strcat(adir, dirname);
					if (ext[0] != '\0') {
						strcat(adir, ".");
						strcat(adir, ext);
					}
					strcat(adir, "/");
					print_directories(new_cluster, adir, filebytes, num_of_sectors, bytes_per_sector, flag);
					// reset pointer
					lseek(fd, ptr + counter * 32, 0);
				}
			}
		}
		if ((read(fd, buf, sizeof(buf))) < 0) {
			printf("There was a problem reading the next file/entry\n");
			exit(1);
		}
	}
}

void trim(char *str) {
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (isspace(str[begin]))
        begin++;

    while ((end >= begin) && isspace(str[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0'; // Null terminate string.
}

void print_files(char *buf, char *directory, char *flag) {
    char filename[256], file[9], extension[4];
    unsigned short date, time;
    unsigned short month, day,  year, hour, minute, second;
    char attributes[] = "----";
    unsigned filesize;

    unsigned short dir_cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
    strncpy(file, buf, 8);
    strncpy(extension, buf+8, 3);
    file[8] = '\0';
    extension[3] = '\0';
    trim(file);
    trim(extension);
    strcpy(filename, directory);
    strcat(filename, file);
    if (extension[0] != '\0') {
        strcat(filename, ".");
        strcat(filename, extension);
    }

    if (strcmp("-l", flag) == 0) {
        time = ((unsigned short) buf[22]&0xff) | ((unsigned short) buf[23]&0xff)<<8;
        date = ((unsigned short) buf[24]&0xff) | ((unsigned short) buf[25]&0xff)<<8;
        second = (time & 0x1f) % 60;
        minute = time>>5 & 0x3f;
        hour = time>>11 & 0x1f;
        day = date & 0x1f;
        month = date>>5 & 0xf;
        year = (date>>9 & 0x7f) + 1980;
        if (buf[11]&0x1) attributes[1] = 'R';
        if (buf[11]&0x2) attributes[2] = 'H';
        if (buf[11]&0x4) attributes[3] = 'S';
        if (buf[11]&0x20) attributes[0] = 'A';

        fprintf(stdout, "-%-9s", attributes);
        fprintf(stdout, "%2.2d/%2.2d/%4d %2.2d:%2.2d:%-10.2d", month, day, year, hour, minute, second);
        if (buf[11]&0x10) {
                fprintf(stdout, "%-10s     ", "<DIR>");
        } else {
                filesize = (buf[31]&0xff) << 24 | (buf[30] & 0xff) << 16 | (buf[29]&0xff) << 8 | (buf[28] & 0xff);
                fprintf(stdout, "%10d     ", filesize);
        }
        fprintf(stdout, "%-40s", filename);
        fprintf(stdout, "%10d\n", dir_cluster);
    } else {
        fprintf(stdout, "%-40s", filename);
        if (buf[11]&0x10) {
                fprintf(stdout, "\t%s", "<DIR>");
        }
        fprintf(stdout, "\n");
    }
}

void traverse(char* flag) {
	if ((fd = open("temp_image", O_RDONLY)) >= 0) {
		// opened the temp file
	} else {
		fprintf(stdout, "The temp file was not mounted, check location and filename and try again.");
	}

	if ((lseek(fd, SEEK_SET, SEEK_SET)) != 0) {
		fprintf(stdout, "There was a problem setting pointer to beginning of temp file\n");
		exit(1);
	}

	if ((read(fd, buf, sizeof(buf)) < 0)){
		fprintf(stdout, "Error reading from temp file, try again.\n");
		exit(1);
	}


    //unsigned short bytes_per_sector; 	/* the number of bytes per sector */
    unsigned short low, high, fat_tables, values, fat_sectors, sectors, rootbytes, filebytes;
    char directory[256], file[9], extension[4];

    low = ((unsigned short) buf[11]) & 0xff;
	high = ((unsigned short) buf[12]) & 0xff;
	bytes_per_sector = low | (high << 8);
	num_of_sectors = ((unsigned short) buf[13]) & 0xff;
	fat_tables = ((unsigned short) buf[16]) & 0xff;
	low = ((unsigned short) buf[17]) & 0xff;
	high = ((unsigned short) buf[18]) & 0xff;
	values = low | (high << 8);
	low = ((unsigned short) buf[22]) & 0xff;
	high = ((unsigned short) buf[23]) & 0xff;
	fat_sectors = low | (high << 8);

	fatbytes = fat_sectors * bytes_per_sector;
	fat_buffer = (char *) malloc(fatbytes);

	if ((lseek(fd, bytes_per_sector, SEEK_SET)) != bytes_per_sector) {
		fprintf(stdout, "There was an issue setting the cursor of temp file\n");
		exit(1);
	}

	if ((read(fd, fat_buffer, fatbytes)) != fatbytes) {
		fprintf(stdout, "There was an error reading the temp file\n");
		exit(1);
	}


    sectors = values * 32 / bytes_per_sector;
    rootbytes = fat_sectors * fat_tables + 1;
    filebytes = rootbytes + sectors;

    strcpy(directory, "/");

    if (strcmp("-l", flag) == 0) {
        fprintf(stdout, " *****************************\n");
        fprintf(stdout, " ** FILE ATTRIBUTE NOTATION **\n");
        fprintf(stdout, " ** **\n");
        fprintf(stdout, " ** R ------ READ ONLY FILE **\n");
        fprintf(stdout, " ** S ------ SYSTEM FILE **\n");
        fprintf(stdout, " ** H ------ HIDDEN FILE **\n");
        fprintf(stdout, " ** A ------ ARCHIVE FILE **\n");
        fprintf(stdout, " *****************************\n\n");
    }

    for (int i = 0;i < values; i++) {
        // go to root entry
        if ((lseek(fd, rootbytes * bytes_per_sector + i * 32, 0)) != rootbytes * bytes_per_sector + i * 32) {
            fprintf(stdout, "There was an error reading entries in temp file \n");
            exit(1);
        }

        if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
            fprintf(stdout, "There was an error reading directory \n");
            exit(1);
        }

        // skip deleted files or free space
        if (((unsigned short) (buf[0]&0xff) == 0xe5) || ((unsigned short) (buf[0]&0xff) == 0x0) ||
        		((unsigned short) (buf[11]&0x08) == 0x08)) {
            continue;
        }

        print_files(buf, directory, flag);
        if (buf[11] & 0x10) {
            cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
            strncpy(file, buf, 8);
            strncpy(extension, buf+8, 3);
            file[8] = '\0';
            extension[3] = '\0';
            trim(file);
            trim(extension);
            strcat(directory, file);
            if (extension[0] != '\0') {
                strcat(directory, ".");
                strcat(directory, extension);
            }
            strcat(directory, "/");
            print_directories(cluster, directory, filebytes, num_of_sectors, bytes_per_sector, flag);
            // go back to root dir
            strcpy(directory, "/");
        }
    }
    free(fat_buffer);
    close(fd);
    remove("temp_image");
}
