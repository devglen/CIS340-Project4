Description:  
    The program allows a user to access data on a floppy disk. The operations
    available to the user are: help, structure, traverse, 
    showsector, showfat, and exit. The user has access to built in Linux commands as
    long as they add the proper path via the “path” shell command. The user can also
    change the current working directory using the “cd” shell command but be aware 
    this will affect the internal commands if they change the directory without changing
    it back before executing the structure, traverse. et. al commands. The user can also 
    use output redirection and pipe feature with the internal commands as well as 
    chain these two together by piping then redirecting the output to a file.

Member Contributions:
    Glen Fannin     33.4%
    Derek Morey     33.3%
    Robert Trebar   33.3%

Compilation instructions:
    1. type make
    2. type ./main
    3. use commands structure, traverse, showsector, and showfat to access data on the floppy disk.
    4. to get help with the commands, type help on the command line.
    5. type path + [path name] to add an environment path 
    6. type path to view the current path 
    7. type path - [path name] to remove an existing path 
    8. type cd to change the current working directory 
    9. for output redirection type [any internal command] > [any filename]
    10. for piping [any internal command] | wc [or any linux command]
    11. for chaining pipe and redirection [any internal command] | wc > [any filename]
    12. to exit the program, type quit in the command line.
    
Sample Run:
	Glens-Air:CIS-340-Project3-master Glen$ make
	gcc -std=gnu99 -Wall -g -c main.c
	gcc -std=gnu99 -Wall -g -c flop.c
	gcc main.o flop.o -o main
	gcc -std=gnu99 -Wall -g -c help.c
	gcc help.o -o help
	gcc -std=gnu99 -Wall -g -c showfat.c
	gcc showfat.o -o showfat
	gcc -std=gnu99 -Wall -g -c showsector.c
	gcc showsector.o -o showsector
	gcc -std=gnu99 -Wall -g -c structure.c
	gcc structure.o -o structure
	gcc -std=gnu99 -Wall -g -c traverse.c
	gcc traverse.o -o traverse
	Glens-Air:CIS-340-Project3-master Glen$ ./main

	flop: help
	The available commands are:
	    help                    - display a list of available commands.
	    cd <path>               - change directories. 
	    path [+][-] [path]      - print current path or modify the path. 
	    structure               - list the structure of the floppy disk image.
	    traverse [-l]           - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.
	    showsector <sector_num> - show the content of the given sector.
	    showfat                 - show the content of the FAT table.
	    exit                    - exit the floppy shell 
	
	flop: structure 
	    Structure of the floppy image: 
	    
	    number of fats: 	2
	    sectors used by fat: 	9
	    sectors per cluster: 	1
	    number of ROOT Entries: 	224
	    number of bytes per sector: 	512
	    ---Sector #---     ---Sector Types---
		   0                  BOOT        
		01 -- 09              FAT1
		10 -- 18              FAT2
		19 -- 32              ROOT DIRECTORY
		
	flop: traverse
	    /DIR1                                   	<DIR>
	    /DIR1/.                                 	<DIR>
	    /DIR1/..                                	<DIR>
	    /DIR1/FILE1.TXT                         
	    /DIR1/FILE2.TXT                         
	    /DIR1/FILE3.TXT                         
	    /FILE1.TXT                              
	    /FILE2.TXT                              
	    /FILE3.TXT                              
	    
	flop: traverse -l 
	    *****************************
	    ** FILE ATTRIBUTE NOTATION **
	    ** **
	    ** R ------ READ ONLY FILE **
	    ** S ------ SYSTEM FILE **
	    ** H ------ HIDDEN FILE **
	    ** A ------ ARCHIVE FILE **
	    *****************************
	   
	   -----     02/25/2015 23:15:26        <DIR>          /DIR1                                            3 
	   -----     02/25/2015 23:14:23        <DIR>          /DIR1/.                                          3 
	   -----     02/25/2015 23:14:23        <DIR>          /DIR1/..                                         0 
	   -A---     02/25/2015 23:15:22                15     /DIR1/FILE1.TXT                                  7 
	   -A---     02/25/2015 23:15:24                15     /DIR1/FILE2.TXT                                  8 
	   -A---     02/25/2015 23:15:26                15     /DIR1/FILE3.TXT                                  9 
	   -A---     02/25/2015 23:15:10                15     /FILE1.TXT                                       4 
	   -A---     02/25/2015 23:15:13                15     /FILE2.TXT                                       5 
	   -A---     02/25/2015 23:15:18                15     /FILE3.TXT                                       6
	
	flop: showsector 10
	
hex dump of sector : 10
	 0 	 1 	 2 	 3 	 4 	 5 	 6 	 7 	 8 	 9 	 A 	 B 	 C 	 D 	 E 	 F
 0 	 f0 	 ff 	 ff 	 0 	 f0 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 0 
 10 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 20 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 30 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 40 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 50 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 60 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 70 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 80 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 90 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 a0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 b0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 c0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 d0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 e0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 f0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 100 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 110 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 120 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 130 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 140 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 150 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 160 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 170 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 180 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 190 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1a0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1b0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1c0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1d0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1e0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1f0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 

	flop: showfat

	 0	 1	 2	 3	 4	 5	 6	 7	 8	 9	 a	 b	 c	 d	 e	 f
 	 		 FREE	 fff	 fff	 fff	 fff	 fff	 fff	 fff	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 10	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 20	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 30	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 40	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 50	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 60	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 70	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 80	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 90	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 100	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 110	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 120	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 130	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 140	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 150	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 160	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 170	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 180	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 190	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 1f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 200	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 210	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 220	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 230	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 240	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 250	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 260	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 270	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 280	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 290	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 2f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 300	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 310	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 320	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 330	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 340	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 350	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 360	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 370	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 380	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 390	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 3f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 400	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 410	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 420	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 430	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 440	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 450	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 460	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 470	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 480	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 490	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 4f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 500	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 510	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 520	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 530	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 540	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 550	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 560	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 570	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 580	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 590	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 5f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 600	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 610	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 620	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 630	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 640	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 650	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 660	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 670	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 680	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 690	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 6f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 700	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 710	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 720	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 730	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 740	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 750	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 760	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 770	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 780	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 790	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 7f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 800	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 810	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 820	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 830	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 840	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 850	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 860	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 870	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 880	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 890	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 8f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 900	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 910	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 920	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 930	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 940	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 950	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 960	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 970	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 980	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 990	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9a0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9b0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9c0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9d0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9e0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 9f0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a00	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a10	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a20	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a30	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a40	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a50	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a60	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a70	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a80	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 a90	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 aa0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 ab0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 ac0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 ad0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 ae0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 af0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b00	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b10	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b20	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b30	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b40	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b50	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b60	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b70	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b80	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 b90	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 ba0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 bb0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 bc0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 bd0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 be0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE
 bf0	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE	 FREE

	flop: path
	path: 
	flop: path + /bin
	path: /bin
	flop: path
	path: /bin
	flop: path - /bin
	path: 
	flop: path
	path: 
	flop: ls
	There was an invalid command in command string.
	
	flop: path + /bin
	path: /bin
	flop: ls
	README.txt	flop.o		help.o		main.c		showfat		showsector	structure	traverse
	flop.c		help		imagefile.img	main.o		showfat.c	showsector.c	structure.c	traverse.c
	flop.h		help.c		main		makefile	showfat.o	showsector.o	structure.o	traverse.o
	
	flop: ps aux
	USER              PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
	Glen              543   1.6  9.2  4697180 387076   ??  S     1:25PM   2:13.34 /Users/Glen/Downloads/eclipse 4/Eclipse.app/Contents/MacOS/eclipse
	Glen              309   0.9  0.8  2573520  33124   ??  S     1:22PM   0:28.34 /Applications/Utilities/Terminal.app/Contents/MacOS/Terminal -psn_0_20485
	_windowserver     223   0.6  1.9  3613944  78664   ??  Ss    1:22PM   1:31.62 /System/Library/Frameworks/ApplicationServices.framework/Frameworks/CoreGraphics.fr
	Glen              311   0.3  6.0  4177880 253088   ??  S     1:22PM   2:30.94 /Applications/Komodo Edit 8.app/Contents/MacOS/komodo-bin -psn_0_24582
	Glen              852   0.0  0.0  2461020   1360 s000  S     2:01PM   0:00.02 -bash
	root              851   0.0  0.1  2468972   2808 s000  Ss    2:01PM   0:00.03 login -pf Glen
	Glen              846   0.0  0.1  2492480   2932   ??  S     1:57PM   0:00.03 /System/Library/Frameworks/ApplicationServices.framework/Frameworks/PrintCore.frame
	Glen              838   0.0  0.7  2571464  31008   ??  S     1:53PM   0:15.13 /Applications/TextEdit.app/Contents/MacOS/TextEdit -psn_0_213044
	root              704   0.0  0.1  2469792   3452   ??  Ss    1:47PM   0:00.05 /usr/libexec/syspolicyd
	Glen              667   0.0  0.9  2710180  39168   ??  S     1:37PM   0:02.52 /Applications/Firefox.app/Contents/MacOS/plugin-container.app/Contents/MacOS/plugin
	root              542   0.0  0.0  2469756   1620   ??  Ss    1:24PM   0:00.15 /usr/libexec/systemstatsd
	_spotlight        497   0.0  0.2  2472312   6444   ??  S     1:23PM   0:00.03 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	_spotlight        496   0.0  0.0  2468740   1184   ??  S     1:23PM   0:00.02 /usr/sbin/distnoted agent
	Glen              478   0.0  0.2  2493976   7628   ??  S     1:23PM   0:00.04 /System/Library/PrivateFrameworks/CommerceKit.framework/Versions/A/Resources/stored
	Glen              477   0.0  0.3  2536940  12880   ??  S     1:23PM   0:00.10 /System/Library/PrivateFrameworks/CommerceKit.framework/Resources/LaterAgent.app/Co
	Glen              476   0.0  0.2  2497468   9296   ??  S     1:23PM   0:00.30 /System/Library/PrivateFrameworks/CommerceKit.framework/Versions/A/Resources/storea
	Glen              475   0.0  0.2  2468920   6312   ??  S     1:23PM   0:00.03 /System/Library/PrivateFrameworks/CommerceKit.framework/Versions/A/Resources/storel
	Glen              472   0.0  0.0  2469216    864   ??  S     1:23PM   0:00.03 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	Glen              471   0.0  0.4  2512780  18796   ??  S     1:23PM   0:00.67 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	Glen              470   0.0  0.4  2487408  18264   ??  S     1:23PM   0:00.61 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	Glen              469   0.0  0.4  2488960  17272   ??  S     1:23PM   0:00.35 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	Glen              468   0.0  0.3  2481776  13536   ??  S     1:23PM   0:00.27 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	root              457   0.0  0.1  2468888   2568   ??  Ss    1:22PM   0:00.01 /System/Library/CoreServices/CrashReporterSupportHelper server-init
	Glen              454   0.0  0.1  2469924   3756   ??  S     1:22PM   0:00.03 /System/Library/Frameworks/Security.framework/Versions/A/Resources/CloudKeychainPro
	Glen              451   0.0  0.3  2543832  13276   ??  S     1:22PM   0:00.55 /Users/Glen/Downloads/Caffeine.app/Contents/MacOS/Caffeine
	Glen              450   0.0  0.1  2494884   5856   ??  S     1:22PM   0:00.05 /Applications/iTunes.app/Contents/MacOS/iTunesHelper.app/Contents/MacOS/iTunesHelpe
	Glen              446   0.0  0.2  2492572   8292   ??  S     1:22PM   0:00.18 /System/Library/CoreServices/diagnostics_agent
	Glen              445   0.0  0.3  2528328  11560   ??  S     1:22PM   0:00.12 /System/Library/CoreServices/WiFiAgent.app/Contents/MacOS/WiFiAgent
	Glen              443   0.0  0.1  2491964   5504   ??  S     1:22PM   0:00.02 /System/Library/PrivateFrameworks/HelpData.framework/Versions/A/Resources/helpd
	Glen              442   0.0  0.1  2492116   4584   ??  S     1:22PM   0:00.08 /System/Library/CoreServices/cloudpaird
	Glen              441   0.0  0.6  2539568  23076   ??  S     1:22PM   0:00.71 com.apple.photostream-agent
	Glen              440   0.0  0.6  2549096  23196   ??  S     1:22PM   0:00.54 /Applications/AVG AntiVirus.app/Contents/MacOS/AVG AntiVirus -AVGStandaloneInstance
	Glen              439   0.0  0.3  2552496  13616   ??  S     1:22PM   0:00.14 /Users/Glen/Library/Application Support/LastPass/LastPassHelper.app/Contents/MacOS/
	Glen              437   0.0  0.3  2495872  14440   ??  S     1:22PM   0:00.21 /System/Library/CoreServices/AppleIDAuthAgent
	Glen              435   0.0  0.6  2572692  25356   ??  S     1:22PM   0:01.08 /System/Library/CoreServices/NotificationCenter.app/Contents/MacOS/NotificationCent
	Glen              432   0.0  0.4  2536912  17024   ??  S     1:22PM   0:00.12 /System/Library/CoreServices/Keychain Circle Notification.app/Contents/MacOS/Keycha
	Glen              430   0.0  0.2  2492032   6512   ??  S     1:22PM   0:00.04 /System/Library/CoreServices/SocialPushAgent.app/Contents/MacOS/SocialPushAgent
	Glen              428   0.0  0.1  2469432   2608   ??  S     1:22PM   0:00.02 /usr/libexec/spindump_agent
	Glen              427   0.0  0.2  2496776   8160   ??  S     1:22PM   0:00.11 /System/Library/Frameworks/InputMethodKit.framework/Versions/A/XPCServices/com.appl
	Glen              425   0.0  0.4  2540524  16288   ??  S     1:22PM   0:02.42 /System/Library/Services/AppleSpell.service/Contents/MacOS/AppleSpell -psn_0_122910
	Glen              424   0.0  0.3  2499488  12728   ??  S     1:22PM   0:00.20 /System/Library/PrivateFrameworks/DataDetectorsCore.framework/Versions/A/XPCService
	Glen              423   0.0  0.4  2531848  14900   ??  S     1:22PM   0:00.17 /System/Library/PrivateFrameworks/MailService.framework/Versions/A/XPCServices/com.
	Glen              422   0.0  1.4  3686840  56760   ??  Ss    1:22PM   0:00.91 /System/Library/Frameworks/WebKit.framework/Versions/A/XPCServices/com.apple.WebKit
	Glen              421   0.0  0.4  2496684  18588   ??  S     1:22PM   0:00.36 /System/Library/PrivateFrameworks/CoreRecents.framework/Versions/A/Support/recentsd
	Glen              420   0.0  1.6  3713720  65620   ??  Ss    1:22PM   0:01.29 /System/Library/Frameworks/WebKit.framework/Versions/A/XPCServices/com.apple.WebKit
	Glen              418   0.0  0.4  2575776  18052   ??  Ss    1:22PM   0:00.57 /System/Library/Frameworks/AppKit.framework/Versions/C/XPCServices/com.apple.appkit
	Glen              417   0.0  0.3  2541752  10564   ??  S     1:22PM   0:00.32 /System/Library/Image Capture/Support/Image Capture Extension.app/Contents/MacOS/Im
	Glen              416   0.0  0.0  2469420   1872   ??  Ss    1:22PM   0:00.01 /Applications/Preview.app/Contents/XPCServices/com.apple.Preview.TrustedBookmarksSe
	root              413   0.0  1.8  2660148  74084   ??  S     1:22PM   0:15.64 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avgscand -c 4 -g 9cc28b38-62b
	root              412   0.0  0.1  2470756   4680   ??  S     1:22PM   0:00.11 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avgsched
	root              411   0.0  0.1  2473448   4496   ??  S     1:22PM   0:01.08 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avgoad
	root              408   0.0  0.1  2491888   5432   ??  Ss    1:22PM   0:00.04 /System/Library/Frameworks/CoreMediaIO.framework/Versions/A/XPCServices/com.apple.c
	root              407   0.0  0.7  2503492  29872   ??  S     1:22PM   0:02.00 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avgavid
	root              406   0.0  0.2  2503408   7540   ??  Ss    1:22PM   0:00.08 /Applications/AVG AntiVirus.app/Contents/Daemons/infosd
	Glen              405   0.0  0.1  2495200   3980   ??  U     1:22PM   0:00.11 /System/Library/CoreServices/pbs
	Glen              403   0.0  0.2  2493456   8072   ??  S     1:22PM   0:00.06 /System/Library/PrivateFrameworks/BookKit.framework/Versions/A/XPCServices/com.appl
	Glen              401   0.0  8.2  3357052 345328   ??  S     1:22PM   1:21.19 /Applications/Firefox.app/Contents/MacOS/firefox
	Glen              400   0.0  0.6  2499784  24956   ??  SNs   1:22PM   0:01.05 /Applications/Komodo Edit 8.app/Contents/Frameworks/Python.framework/Versions/2.7/R
	root              398   0.0  4.2  2657548 174612   ??  S     1:22PM   0:01.53 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avggmsd
	Glen              396   0.0  0.4  2496792  16888   ??  S     1:22PM   0:00.42 /System/Library/PrivateFrameworks/CommerceKit.framework/Versions/A/Resources/storea
	root              394   0.0  0.1  2469592   6224   ??  Ss    1:22PM   0:00.06 /System/Library/PrivateFrameworks/SoftwareUpdate.framework/Resources/suhelperd
	Glen              393   0.0  0.1  2468988   2792   ??  Ss    1:22PM   0:00.03 /System/Library/PrivateFrameworks/IMFoundation.framework/XPCServices/IMRemoteURLCon
	_softwareupdate   391   0.0  1.1  2525636  47332   ??  Ss    1:22PM   0:03.28 /System/Library/CoreServices/Software Update.app/Contents/Resources/softwareupdated
	_netbios          387   0.0  0.1  2470004   5896   ??  SNs   1:22PM   0:00.05 /usr/sbin/netbiosd
	Glen              385   0.0  0.5  2499284  19868   ??  S     1:22PM   0:01.73 /System/Library/PrivateFrameworks/ParsecUI.framework/Versions/A/Support/SpotlightNe
	Glen              384   0.0  0.8  2516480  32116   ??  U     1:22PM   0:01.47 /System/Library/CoreServices/ScopedBookmarkAgent
	Glen              383   0.0  0.2  2495888  10216   ??  Ss    1:22PM   0:00.13 /System/Library/PrivateFrameworks/CloudDocsDaemon.framework/XPCServices/ContainerMe
	Glen              381   0.0  0.2  2496284   9948   ??  S     1:22PM   0:00.58 /usr/libexec/nsurlsessiond
	root              380   0.0  0.1  2453028   5008   ??  Ss    1:22PM   0:00.09 /usr/libexec/watchdogd
	Glen              379   0.0  0.7  2513256  30596   ??  U     1:22PM   0:03.78 /System/Library/PrivateFrameworks/CloudKitDaemon.framework/Support/cloudd
	root              376   0.0  0.1  2470428   5704   ??  Ss    1:22PM   0:00.08 /Library/CoreMediaIO/Plug-Ins/DAL/AppleCamera.plugin/Contents/Resources/AppleCamera
	Glen              374   0.0  0.1  2468960   3468   ??  Ss    1:22PM   0:00.07 /System/Library/CoreServices/Menu Extras/AirPort.menu/Contents/XPCServices/com.appl
	Glen              372   0.0  0.4  2503588  15340   ??  U     1:22PM   0:02.08 /System/Library/Frameworks/Accounts.framework/Versions/A/Support/accountsd
	Glen              371   0.0  0.3  2500396  11260   ??  S     1:22PM   0:00.07 /System/Library/PrivateFrameworks/CallHistory.framework/Support/CallHistoryPluginHe
	Glen              369   0.0  0.3  2494964  14572   ??  S     1:22PM   0:00.35 /System/Library/PrivateFrameworks/IMCore.framework/imagent.app/Contents/MacOS/image
	Glen              368   0.0  0.1  2492976   4776   ??  S     1:22PM   0:00.07 /System/Library/PrivateFrameworks/IMDPersistence.framework/XPCServices/IMDPersisten
	Glen              367   0.0  0.5  2524504  21364   ??  S     1:22PM   0:00.44 /System/Library/PrivateFrameworks/MessagesKit.framework/Resources/soagent.app/Conte
	Glen              365   0.0  0.2  2497636   9228   ??  S     1:22PM   0:00.38 /usr/libexec/pkd
	Glen              364   0.0  0.5  2542400  21644   ??  Ss    1:22PM   0:00.27 /System/Library/CoreServices/Dock.app/Contents/XPCServices/com.apple.dock.extra.xpc
	Glen              362   0.0  0.5  2507016  18940   ??  S     1:22PM   0:00.36 /usr/libexec/sharingd
	Glen              361   0.0  0.1  2492320   4344   ??  S     1:22PM   0:00.08 /System/Library/CoreServices/lsuseractivityd
	root              360   0.0  0.3  2472924  11232   ??  Ss    1:22PM   0:00.10 /System/Library/CoreServices/backupd.bundle/Contents/Resources/TMCacheDelete
	Glen              359   0.0  0.1  2496096   5296   ??  S     1:22PM   0:00.06 /System/Library/CoreServices/iconservicesagent
	root              358   0.0  0.1  2471876   3264   ??  Ss    1:22PM   0:00.20 /System/Library/PrivateFrameworks/CacheDelete.framework/deleted
	Glen              355   0.0  0.3  2529776  11300   ??  S     1:22PM   0:00.11 /System/Library/CoreServices/AirPlayUIAgent.app/Contents/MacOS/AirPlayUIAgent --lau
	Glen              354   0.0  0.7  2586256  29196   ??  S     1:22PM   0:01.08 /System/Library/CoreServices/Spotlight.app/Contents/MacOS/Spotlight
	_coreaudiod       353   0.0  0.1  2492800   2264   ??  Us    1:22PM   0:00.07 /System/Library/Frameworks/CoreAudio.framework/Versions/A/XPCServices/com.apple.aud
	root              352   0.0  0.1  2495924   3552   ??  Ss    1:22PM   0:00.03 /System/Library/PrivateFrameworks/TCC.framework/Resources/tccd system
	_coreaudiod       349   0.0  0.2  2498820   9072   ??  Ss    1:22PM   0:00.82 /usr/sbin/coreaudiod
	Glen              348   0.0  1.5  2624896  62052   ??  S     1:22PM   0:22.87 /System/Library/CoreServices/Finder.app/Contents/MacOS/Finder
	Glen              346   0.0  0.5  2561596  20576   ??  S     1:22PM   0:01.00 /System/Library/CoreServices/SystemUIServer.app/Contents/MacOS/SystemUIServer
	Glen              345   0.0  0.8  2593772  32848   ??  S     1:22PM   0:02.72 /System/Library/CoreServices/Dock.app/Contents/MacOS/Dock
	Glen              344   0.0  0.5  2512696  19852   ??  U     1:22PM   0:00.63 /System/Library/PrivateFrameworks/TelephonyUtilities.framework/callservicesd
	root              343   0.0  0.1  2474344   3568   ??  Ss    1:22PM   0:00.20 /usr/sbin/filecoordinationd
	Glen              340   0.0  0.1  2527440   6220   ??  S     1:22PM   0:03.29 /System/Library/Frameworks/ApplicationServices.framework/Frameworks/ATS.framework/S
	Glen              339   0.0  0.2  2474944   8472   ??  S     1:22PM   0:00.82 /usr/libexec/nsurlstoraged
	Glen              338   0.0  0.4  2551288  15960   ??  S     1:22PM   0:00.29 /System/Library/CoreServices/CoreServicesUIAgent.app/Contents/MacOS/CoreServicesUIA
	Glen              337   0.0  0.0  2460412   1060   ??  S     1:22PM   0:00.01 /usr/sbin/pboard
	Glen              336   0.0  0.4  2505332  17696   ??  S     1:22PM   0:00.92 /System/Library/PrivateFrameworks/IDS.framework/identityservicesd.app/Contents/MacO
	Glen              335   0.0  0.6  2547996  26456   ??  S     1:22PM   0:00.62 /System/Library/PrivateFrameworks/InternetAccounts.framework/Versions/A/XPCServices
	Glen              333   0.0  0.5  2498500  20784   ??  Ss    1:22PM   0:00.53 /System/Library/PrivateFrameworks/CalendarAgent.framework/Versions/A/XPCServices/Ca
	Glen              332   0.0  0.1  2494572   5028   ??  S     1:22PM   0:00.22 /usr/libexec/secd
	Glen              330   0.0  0.2  2498384   6596   ??  S     1:22PM   0:00.91 /System/Library/PrivateFrameworks/TCC.framework/Resources/tccd
	Glen              329   0.0  0.2  2493452   8960   ??  S     1:22PM   0:00.47 /usr/libexec/secinitd
	Glen              328   0.0  0.3  2492088  11620   ??  S     1:22PM   0:00.04 /System/Library/PrivateFrameworks/AskPermission.framework/Versions/A/Resources/askp
	Glen              327   0.0  0.3  2500416  12524   ??  S     1:22PM   0:00.09 /System/Library/PrivateFrameworks/CallHistory.framework/Support/CallHistorySyncHelp
	Glen              325   0.0  0.3  2492576  13876   ??  S     1:22PM   0:00.20 /usr/libexec/fmfd
	Glen              324   0.0  0.6  2502328  23296   ??  S     1:22PM   0:01.02 /System/Library/PrivateFrameworks/CloudDocsDaemon.framework/Versions/A/Support/bird
	Glen              323   0.0  0.7  2511384  29156   ??  S     1:22PM   0:04.26 /System/Library/PrivateFrameworks/CalendarAgent.framework/Executables/CalendarAgent
	Glen              320   0.0  0.1  2495260   6240   ??  S     1:22PM   0:00.66 /usr/sbin/usernoted
	Glen              319   0.0  2.4  2770136 102712   ??  S     1:22PM   0:06.05 /Applications/Keynote.app/Contents/MacOS/Keynote -psn_0_45067
	root              317   0.0  0.8  2518000  34744   ??  Ss    1:22PM   0:01.09 /usr/libexec/amfid
	Glen              315   0.0  0.0  2423340     24   ??  T     1:22PM   0:00.00 /Applications/Google Chrome.app/Contents/MacOS/Google Chrome -psn_0_36873
	Glen              313   0.0  0.9  2655872  36656   ??  U     1:22PM   0:01.47 /Applications/Preview.app/Contents/MacOS/Preview -psn_0_32776
	Glen              312   0.0  2.0  3685148  85056   ??  S     1:22PM   0:17.77 /Applications/Mail.app/Contents/MacOS/Mail -psn_0_28679
	Glen              307   0.0  0.1  2471992   3852   ??  S     1:22PM   0:01.00 /usr/sbin/cfprefsd agent
	Glen              305   0.0  0.1  2470788   4332   ??  S     1:22PM   0:01.19 /usr/sbin/distnoted agent
	Glen              303   0.0  0.3  2497016  12708   ??  S     1:22PM   0:00.65 /usr/libexec/UserEventAgent (Aqua)
	root              300   0.0  0.1  2492496   2140   ??  Ss    1:22PM   0:00.15 /usr/libexec/securityd_service
	root              287   0.0  0.1  2493200   3492   ??  Ss    1:22PM   0:00.09 /usr/sbin/diskmanagementd
	_nsurlstoraged    277   0.0  0.1  2469056   2772   ??  Ss    1:22PM   0:00.02 /usr/libexec/nsurlstoraged
	root              274   0.0  0.0  2469216   1408   ??  Ss    1:22PM   0:00.09 /System/Library/Frameworks/Security.framework/Versions/A/XPCServices/com.apple.Code
	root              266   0.0  0.0  2469336   1848   ??  Ss    1:22PM   0:00.18 sysmond
	root              265   0.0  0.0  2469224   1024   ??  Ss    1:22PM   0:00.01 /usr/libexec/networkd_privileged
	root              264   0.0  0.1  2469660   5648   ??  Ss    1:22PM   0:00.11 /System/Library/PrivateFrameworks/AmbientDisplay.framework/Versions/A/XPCServices/c
	_networkd         263   0.0  0.1  2476180   5204   ??  Ss    1:22PM   0:00.39 /usr/libexec/networkd
	root              260   0.0  0.1  2472336   3236   ??  Ss    1:22PM   0:00.04 /usr/libexec/nehelper
	root              259   0.0  0.2  2494320   6404   ??  Ss    1:22PM   0:04.98 /usr/libexec/ApplicationFirewall/socketfilterfw
	root              258   0.0  0.1  2471356   5888   ??  Ss    1:22PM   0:00.17 /usr/libexec/corestoraged
	root              257   0.0  0.1  2469072   2656   ??  Ss    1:22PM   0:00.02 /System/Library/CryptoTokenKit/com.apple.ifdreader.slotd/Contents/MacOS/com.apple.i
	root              256   0.0  0.0  2471152   1304   ??  Ss    1:22PM   0:00.32 /usr/sbin/ntpd -c /private/etc/ntp-restrict.conf -n -g -p /var/run/ntpd.pid -f /var
	root              255   0.0  0.1  2492024   5680   ??  Ss    1:22PM   0:00.03 /usr/libexec/usbd
	_nsurlsessiond    254   0.0  0.1  2469304   5708   ??  Ss    1:22PM   0:00.03 /usr/libexec/nsurlsessiond --privileged
	root              252   0.0  0.0  2469280   1136   ??  Ss    1:22PM   0:00.01 /usr/libexec/discoveryd_helper --loglevel Detailed --logclass Everything --logto as
	root              251   0.0  0.0  2494092   1380   ??  Ss    1:22PM   0:00.09 /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/CVMServer
	root              247   0.0  0.1  2470480   2752   ??  Ss    1:22PM   0:00.02 /System/Library/PrivateFrameworks/CoreSymbolication.framework/coresymbolicationd
	root              246   0.0  1.1  2992208  45516   ??  Us    1:22PM   0:07.33 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Ver
	root              245   0.0  0.2  2495996  10364   ??  Ss    1:22PM   0:00.46 /usr/libexec/findmydeviced
	root              226   0.0  0.2  2492496   6864   ??  Ss    1:22PM   0:00.05 /usr/libexec/secinitd
	root              224   0.0  0.1  2469604   2680   ??  Ss    1:22PM   0:00.02 /System/Library/Frameworks/CryptoTokenKit.framework/ctkd -s
	root              176   0.0  0.1  2503516   3984   ??  Ss    1:22PM   0:00.13 /usr/libexec/sandboxd -n PluginProcess -n 
	root              119   0.0  0.1  2471660   2696   ??  Ss    1:22PM   0:00.02 /System/Library/Frameworks/PCSC.framework/Versions/A/XPCServices/com.apple.ctkpcscd
	root               93   0.0  0.1  2496364   5852   ??  Ss    1:22PM   0:00.42 /System/Library/Frameworks/Security.framework/Versions/A/XPCServices/authd.xpc/Cont
	root               85   0.0  0.1  2471392   3148   ??  Ss    1:22PM   0:01.41 /usr/sbin/cfprefsd daemon
	root               83   0.0  0.0  2471300   1068   ??  Ss    1:22PM   0:00.01 /usr/libexec/diagnosticd
	_distnote          81   0.0  0.0  2471312   1632   ??  Us    1:22PM   0:00.11 /usr/sbin/distnoted daemon
	root               80   0.0  0.2  2503508   9860   ??  Ss    1:22PM   0:01.14 /System/Library/CoreServices/coreservicesd
	root               77   0.0  0.0  2471852   1612   ??  Ss    1:22PM   0:01.27 /usr/sbin/notifyd
	root               76   0.0  0.1  2493496   5700   ??  Ss    1:22PM   0:01.57 /usr/libexec/taskgated -s
	root               75   0.0  0.1  2469904   4036   ??  Ss    1:22PM   0:28.65 /usr/libexec/hidd
	root               73   0.0  0.0  2469240   1032   ??  Ss    1:22PM   0:00.01 /usr/sbin/KernelEventAgent
	root               72   0.0  0.1  2468924   2704   ??  Ss    1:22PM   0:00.03 /System/Library/CoreServices/logind
	Glen               71   0.0  0.4  2517944  17316   ??  Ss    1:22PM   0:01.01 /System/Library/CoreServices/loginwindow.app/Contents/MacOS/loginwindow console
	root               70   0.0  0.1  2503080   4644   ??  Ss    1:22PM   0:00.11 /System/Library/PrivateFrameworks/GenerationalStorage.framework/Versions/A/Support/
	root               69   0.0  0.0  2469260   1284   ??  Ss    1:22PM   0:00.01 /usr/libexec/stackshot -t -O
	root               64   0.0  0.1  2469524   2568   ??  Ss    1:22PM   0:00.02 autofsd
	root               63   0.0  0.1  2493132   4404   ??  Ss    1:22PM   0:00.18 /usr/sbin/blued
	_locationd         60   0.0  0.2  2502368   8320   ??  Ss    1:22PM   0:00.43 /usr/libexec/locationd
	root               58   0.0  0.1  2495168   4904   ??  Ss    1:22PM   0:01.21 /usr/sbin/securityd -i
	_usbmuxd           57   0.0  0.1  2471460   3260   ??  Ss    1:22PM   0:00.09 /System/Library/PrivateFrameworks/MobileDevice.framework/Versions/A/Resources/usbmu
	root               56   0.0  0.2  2497172   7296   ??  Ss    1:22PM   0:01.95 /System/Library/CoreServices/launchservicesd
	root               55   0.0  0.3  2495752  11516   ??  Ss    1:22PM   0:00.93 /System/Library/PrivateFrameworks/ApplePushService.framework/apsd
	_mdnsresponder     54   0.0  0.3  2502760  11420   ??  Us    1:22PM   0:01.51 /usr/libexec/discoveryd --udsocket standard --loglevel Basic --logclass Everything 
	root               52   0.0  0.1  2472724   4160   ??  Ss    1:22PM   0:00.07 /usr/sbin/wirelessproxd
	root               51   0.0  4.1  2638256 172044   ??  Ss    1:22PM   0:02.67 /Applications/AVG AntiVirus.app/Contents/Backend//bin/avgd
	root               50   0.0  0.3  2511856  12640   ??  Ss    1:22PM   0:01.96 /usr/libexec/opendirectoryd
	root               49   0.0  0.1  2496552   5720   ??  Ss    1:22PM   0:00.07 /System/Library/PrivateFrameworks/WirelessDiagnostics.framework/Support/awdd
	root               47   0.0  0.1  2469508   5432   ??  Ss    1:22PM   0:00.02 /usr/libexec/wdhelper
	root               45   0.0  0.2  2501980   9648   ??  Ss    1:22PM   0:01.73 /usr/libexec/coreduetd
	root               42   0.0  0.0  2491812   1908   ??  Ss    1:22PM   0:00.10 /usr/libexec/diskarbitrationd
	root               41   0.0  0.1  2469404   2716   ??  Ss    1:22PM   0:00.02 /System/Library/CoreServices/iconservicesagent
	_iconservices      40   0.0  0.1  2469404   2832   ??  Ss    1:22PM   0:00.03 /System/Library/CoreServices/iconservicesd
	root               36   0.0  0.8  2569436  33080   ??  Ss    1:22PM   0:09.00 /System/Library/Frameworks/CoreServices.framework/Frameworks/Metadata.framework/Sup
	root               35   0.0  0.2  2473256   7568   ??  SNs   1:22PM   0:00.15 /usr/libexec/warmd
	root               33   0.0  0.2  2496296  10468   ??  Ss    1:22PM   0:02.06 /usr/libexec/airportd
	root               30   0.0  0.1  2491916   2124   ??  Ss    1:22PM   0:00.63 /System/Library/CoreServices/powerd.bundle/powerd
	root               29   0.0  0.1  2497928   5856   ??  Ss    1:22PM   0:01.28 /usr/libexec/configd
	_appleevents       28   0.0  0.1  2495476   4852   ??  Ss    1:22PM   0:00.22 /System/Library/CoreServices/appleeventsd --server
	root               26   0.0  0.1  2469032   5384   ??  Ss    1:22PM   0:00.04 /usr/libexec/thermald
	root               24   0.0  0.1  2477336   3244   ??  Ss    1:22PM   0:01.15 /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/FSEvents.fr
	root               23   0.0  0.3  2498232  14128   ??  Ss    1:22PM   0:01.90 /usr/libexec/kextd
	root               21   0.0  0.0  2472432   1484   ??  Ss    1:22PM   0:00.62 /usr/sbin/syslogd
	root               20   0.0  0.4  2499408  17072   ??  Ss    1:22PM   0:01.16 /usr/libexec/UserEventAgent (System)
	root              993   0.0  0.0  2432788    668 s000  R+    2:15PM   0:00.00 ps aux
	root                1   0.0  0.3  2493628  11976   ??  Ss    1:22PM   0:04.77 /sbin/launchd
	Glen              990   0.0  0.0  2444016    308 s000  S+    2:14PM   0:00.00 ./main
	Glen              989   0.0  0.2  2492960   7744   ??  S     2:12PM   0:00.09 /System/Library/PrivateFrameworks/AOSKit.framework/Versions/A/XPCServices/com.apple
	Glen              973   0.0  0.0  2435824    592 s000  S+    2:03PM   0:00.01 ./main
	
	flop: structure | grep ROOT
	number of ROOT Entries: 	224
	    19 -- 32              ROOT DIRECTORY
	    
	flop: showfat | wc
	194    3277   19408
	
	flop: showsector 10 > mysectorfile
	
		***** CONTENTS OF SECTOR FILE NOT APART OF RUNNING PROGRAM ******
		
hex dump of sector : 10
	 0 	 1 	 2 	 3 	 4 	 5 	 6 	 7 	 8 	 9 	 A 	 B 	 C 	 D 	 E 	 F
 0 	 f0 	 ff 	 ff 	 0 	 f0 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 ff 	 0 
 10 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 20 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 30 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 40 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 50 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 60 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 70 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 80 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 90 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 a0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 b0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 c0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 d0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 e0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 f0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 100 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 110 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 120 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 130 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 140 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 150 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 160 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 170 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 180 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 190 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1a0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1b0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1c0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1d0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1e0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 
 1f0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 	 0 

		******** END OF CONTENTS OF MYSECTORFILE OUTPUT *********

	flop: structure | grep DIRECTORY > mygreppedfile
	
		******** CONTENTS OF MYGREPPEDFILE NOT APART OF PROGRAM *******
		
		        19 -- 32              ROOT DIRECTORY
			
		******** END OF CONTENTS OF MYGREPPEDFILE ****************

	flop: cd /Users/Glen/Documents

	flop: ls
	CIS340					hw1					quiz3_art286.pages			transcribe.pages
	art_research.pages			hw1.c					temp					ust302_research_paper_topics.pages
	c_workspace				lecture_notes				temp.c					wallet.dat
	data.txt				mainfat.c				test.c					workspace
	glenfannin_midterm.pages		old_hw					topics ust302.txt
	
	flop: exit 
	    Exiting the floppy disk shell... 

Bugs:
    I have noticed a minor issue that is intermittent, when exiting the program after executing multiple commands and having the program run for a
    while you will need to type and execute the exit command twice for the prorgam to actually quit. see example below:
    
	flop: exit
	Exiting the floppy disk shell... 
	
	flop: exit
	Exiting the floppy disk shell...
	Glens-Air:CIS-340-Project3-master Glen$
	
    As you can see on the second exit attempt is when the program actually quit. I am unable to figure out why this is happening, also since it does not always
    occur it is difficult to debug. 
