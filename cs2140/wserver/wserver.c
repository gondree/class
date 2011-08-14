#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include "http_support.h"

//
// Globals and constants
//


//
// External variables
//
extern char *server_root;

//
// Function prototypes and functions
//
void handle_connection(int fd);

void usage(const char* arg)
{
	// TODO: need a usage message  
    exit(0);
}

//
// Main
//
int main(int argc, char *argv[])
{
	// TODO: need networking logic
    return 0;
}

// 
// The function to handle a client connection
//
void handle_connection(int fd)
{
    http_req req;
    FILE *rx, *tx;

    exit_msg((fd < 0) || (fd > FD_SETSIZE), "bad fd");
    
    // for streams with sockets, need one for read and one for write
    rx = fdopen(fd, "r");
    tx = fdopen(dup(fd), "w");

    init_req(&req);
    http_get_request(rx, &req);
    http_process_request(&req);
    http_response(tx, &req);

	shutdown(fileno(rx), SHUT_RDWR);
	fclose(rx);
    fclose(tx);
    free_req(&req);
    return;
}

