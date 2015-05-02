
#include	<strings.h>
#include 	<stdlib.h>
#include	<stdio.h>
#include	<sys/types.h>
#include    	<fcntl.h>
#include    	<string.h>
#include    	<unistd.h>
#include 	"utility.h"

void fmount(char* filename) {
    if ((fd = open(filename, O_RDONLY)) >= 0) {
        return;
    } else {
        fprintf(stdout, "The floppy disk was not mounted, check location and filename and try again.");
        exit(1);
    }
}

void get_sector_data(u_long sector_number) {
    int nread;	/* number of bytes read from the floopy disk */
    off_t lseek_value;
    char boot[32];
    unsigned short sector = sector_number;
    unsigned short lowbyte, highbyte;
    unsigned cursor;
    unsigned short nbytesec; 	/* the number of bytes per sector */
    unsigned short totalsec; 	/* the total number of logical sectors */
	
    lseek_value = lseek(fd, SEEK_SET, SEEK_SET); /* rewind the cursor */
    if (lseek_value != 0) perror("error in setting the file descriptor cursor");
    nread = read(fd, boot, sizeof(boot)); /* read first 32 bytes in boot sector */
    if (nread != sizeof(boot)) perror("Cannot read from the floppy disk!");
    lowbyte = ((unsigned short) boot[11]) & 0xff;
    highbyte = ((unsigned short) boot[12]) & 0xff;
    nbytesec = lowbyte | (highbyte << 8);	/* get the number of bytes per sector */
    lowbyte = ((unsigned short) boot[19]) & 0xff;
    highbyte = ((unsigned short) boot[20]) & 0xff;
    totalsec = lowbyte | (highbyte << 8); 	/* get the number of logical sectors */

    if (sector >= totalsec) perror("the sector number was too large");
    //message.data = (char *) malloc(nbytesec);
    buf = (char *) malloc(nbytesec);
    cursor = sector * nbytesec;
    lseek_value = lseek(fd, cursor, SEEK_SET);
    if (lseek_value != cursor) perror("error in setting the file descriptor cursor");

    if ((nread = read(fd, buf, nbytesec)) != nbytesec) perror("error in reading the sector");
    message.size = nread;
}
