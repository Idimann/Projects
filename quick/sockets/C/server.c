#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in serv; //This is our main socket variable.
int fd; //This is the socket file descriptor that will be used to identify the socket
int conn; //This is the connection file descriptor that will be used to distinguish client connections.
char message[100];

int main(int argc, char* argv[]) {
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8096); //Define the port at which the server will listen for connections.
    serv.sin_addr.s_addr = INADDR_ANY;
    fd = socket(AF_INET, SOCK_STREAM, 0); 

    while(conn = accept(fd, (struct sockaddr *) NULL, NULL)) {
        int pid;
        if((pid = fork()) == 0) {
            while (recv(conn, message, 100, 0)>0) {
                printf("Message Received: %s\n", message);
                //An extra breaking condition can be added here (to terminate the child process)            
                strncpy(message, "", 100);
            }
            exit(0);
        }
    }
}
