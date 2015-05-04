Project Description: 

	Floppy disk communication over a client/server UDP communication. 
	Client communicates with Server with a similar struct, client sends the sector number to server
	sever reads sector from local floppy disk and sends it back to the client for processing/formatting.
	Once Client receives data it processes and displays it based on the user command. Server only accepts  
	communication from one client at any given time. 
	The only requests the server accepts are 
		Request for new connection.
		Request for data in a specific sector of the floppy disk.
		Request for disconnect.
	The commands the clients accepts are: 
		help
		quit
		traverse [-l]
		showsector <sector number>
		structure
		fmount <hostname>
		fumount <hostname>
	

Member Contributions:

    	Glen Fannin:	 % 		
	James Saporito	 %
	Aaron Markoff:	0%
	
Compilation instructions:

	1) Open two terminal Windows (one will be designated as the Server, the other as the Client)
	2) In the first, navigate to the location of the project folder.
	3) Type make to compile the source code
	CLIENT: 
	4) In the first terminal, type ./client (which will start up the floppy shell)
	
	SERVER:
	5) In the second terminal, type ./server imagefile.img (to start the server, where imagefile.img is the name of the 
	floppy image on the local system)
	
	6) Leave the server running and it will wait to accept commands...
	7) In the client terminal, first mount the floppy by typing: fmount <hostname> 
	8) After mounting you have all the available commands available to you 
	(structure, showsector, traverse, help, and quit)
	9) Once complete, run the fumount <hostname> command to unmount the floppy 
	10) Run the quit command to exit the floppy shell.

Sample Run:

        Glens-Air:CIS340-Project4-master Glen$ make
        gcc -std=gnu99 -Wall -g -c server.c
        gcc -std=gnu99 -Wall -g -c utility.c
        gcc server.o utility.o -o server
        gcc -std=gnu99 -Wall -g -c client.c
        gcc -std=gnu99 -Wall -g -c c_util.c
        gcc client.o c_util.o -o client
        Glens-Air:CIS340-Project4-master Glen$ 
        
        Glens-Air:CIS340-Project4-master Glen$ ./server imagefile.img
        RECV_UDP Local socket is: 
          family 2, addr 0.0.0.0, port 13107
        
        Glens-Air:CIS340-Project4-master Glen$ ./client
        flop: 
        
        flop: fmount localhost
        Floppy mounted successfully.
        flop: 
        
        flop: help
        The available commands are:
            help                    - display a list of available commands.
            fmount <hostname>      	- mount the specified image file
            fumount <hostname>      - umount the mounted floppy disk. 
            structure               - list the structure of the floppy disk image.
            traverse [-l]           - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.
            showsector <sector_num> - show the content of the given sector.
            quit                    - quit the floppy shell 
        flop: 
        
        flop: structure 
                        number of FAT:			    2
                        number of sectors used by FAT:	    9
                        number of sectors per cluster:	    1
                        number of ROOT Entries:		  224
                        number of bytes per sector:	  512
                        ---Sector #---     ---Sector Types---
                              0                  BOOT       
                           01 -- 09              FAT1         
                           10 -- 18              FAT2         
                           19 -- 32              ROOT DIRECTORY
        
        flop: 
        
        flop: showsector 10
        hex dump of sector : 10
                 0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f
        
            0   f0   ff   ff    0   40    0   ff   6f    0   ff   ff   ff    9   f0   ff   ff
           10   cf    0   ff   ff   ff   ff    f    1   11   f0   ff   ff   ff   ff   15   f0
           20   ff   17   f0   ff   ff   ff   ff   ff   ff   ff   1d   f0   ff   1f    0    2
           30   ff   ff   ff    0    0    0    0    0    0    0    0    0    0    0    0    0
           40    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           50    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           60    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           70    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           80    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           90    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           a0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           b0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           c0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           d0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           e0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
           f0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          100    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          110    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          120    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          130    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          140    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          150    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          160    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          170    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          180    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          190    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1a0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1b0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1c0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1d0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1e0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
          1f0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
        flop: 
        
        flop: traverse
        /A.CLA                                  
        /ALOOP1.CLA                             
        /ALOOP1.JAV                             
        /ALOOP2.CLA                             
        /ALOOP2.JAV                             
        /ALOOP3.CLA                             
        /ALOOP3.JAV                             
        /B.CLA                                  
        /CONDIT.CLA                             
        /CONDIT.JAV                             
        /D.CLA                                  
        /DEMO.CLA                               
        /DEMO.JAV                               
        /DIR1                                   	<DIR>
        /POLYTEST.CLA                           
        /POLYTEST.JAV                           
        /SOME.CLA                               
        flop: 
        
        flop: traverse -l
         *****************************
         ** FILE ATTRIBUTE NOTATION **
         ** **
         ** R ------ READ ONLY FILE **
         ** S ------ SYSTEM FILE **
         ** H ------ HIDDEN FILE **
         ** A ------ ARCHIVE FILE **
         *****************************
        
        -A---     10/27/2014 13:13:05               670     /A.CLA                                           3
        -A---     10/27/2014 13:13:05               763     /ALOOP1.CLA                                      5
        -A---     10/27/2014 13:13:05               333     /ALOOP1.JAV                                      7
        -A---     10/27/2014 13:13:05               786     /ALOOP2.CLA                                      8
        -A---     10/27/2014 13:13:05               404     /ALOOP2.JAV                                     10
        -A---     10/27/2014 13:13:05               786     /ALOOP3.CLA                                     11
        -A---     10/27/2014 13:13:05               408     /ALOOP3.JAV                                     13
        -A---     10/27/2014 13:13:05               358     /B.CLA                                          14
        -A---     10/27/2014 13:13:05              1067     /CONDIT.CLA                                     15
        -A---     10/27/2014 13:13:05               444     /CONDIT.JAV                                     18
        -A---     10/27/2014 13:13:05               508     /D.CLA                                          19
        -A---     10/27/2014 13:13:05               967     /DEMO.CLA                                       20
        -A---     10/27/2014 13:13:05               648     /DEMO.JAV                                       22
        -----     10/27/2014 13:13:05        <DIR>          /DIR1                                           24
        -A---     10/27/2014 13:13:05               630     /POLYTEST.CLA                                   28
        -A---     10/27/2014 13:13:05              1063     /POLYTEST.JAV                                   30
        -A---     10/27/2014 13:13:05               226     /SOME.CLA                                       33
        flop: 
        
        flop: fumount localhost
        Floppy has been unmounted successfully.
        flop: 
        
        flop: quit
        
         Exiting the floppy disk shell... 
        Glens-Air:CIS340-Project4-master Glen$ 


Bugs:
	None.
