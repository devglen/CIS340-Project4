Server daemon: a single threaded UDP Floppy Disk server, which accepts three API commands:

    Request for new connection.
    Request for data in a specific sector of the floppy disk.
    Request for disconnect.
    An floppy image file is specified as the server execution argument; the server will always keep the image file open during the execution.
    Note: the server does not accept the floppy commands, including structure, traverse and showsector. Instead, the server only provides the raw data, which are the contents of a certain sector from the floppy disk.

The server daemon is expected to serve only one client at a time.

Upon a successful connection, the client will receive a handle (similar to a file descriptor) from the floppy server and use the handle as the reference in all future remote requests.

When a connected client requests for data or disconnection, the floppy daemon must check whether the client's handle is consistent with its port number and inet address associated. If not, the request will be rejected.
Note: the server daemon can only access the floppy disk through the primitive operation, such as read(). Your implementation is not allowed to use system() to execute shell commands.
[60 points] Client Shell (a floppy console): the shell environment allows users to access the remote floppy by using the following commands:

    help: show the commands supported in the floppy shell.
    fmount [hostname]: mount the remote floppy disk.
    fumount [hostname]: umount (disconnect) the remote floppy disk.
    structure: to list the structure of the floppy disck. 
