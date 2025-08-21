#include <stdio.h>
#include "request.h"
#include "io_helper.h"

#define FIFO 1
#define SFF 2


char default_root[] = ".";

//
// ./wserver [-d <basedir>] [-p <portnum>] 
// 
int main(int argc, char *argv[]) {
    int c;
    char *root_dir = default_root;
    int port = 10000;
    int pool = 1;
    int schedule = 1;
    while ((c = getopt(argc, argv, "d:p:")) != -1) //feed in the pool size through here
	switch (c) {
	case 'd':
	    root_dir = optarg;
	    break;
	case 'p':
	    port = atoi(optarg);
	    break;
	default:
	    fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
	    exit(1);
	}
    printf("Please enter the size of the thread pool:");
    scanf("%d", &pool);
    if (pool <1) {
        printf("Error. Aborting.\n");
	return 0;
    }
    printf("Please enter the scheduler method.\nSelect 1 for F.I.F.O or 2 for S.F.F.");
    scanf("%d", &schedule);
    if ( schedule <1 || schedule >2) {
        printf("Error. Aborting.\n");
	return 0;
    }

    // run out of this directory
    chdir_or_die(root_dir);
    
    // now, get to work
    int listen_fd = open_listen_fd_or_die(port);
    while (1) {
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int conn_fd = accept_or_die(listen_fd, (sockaddr_t *) &client_addr, (socklen_t *) &client_len);
	request_handle(conn_fd);
	close_or_die(conn_fd);
    }
    return 0;
}


    


 
