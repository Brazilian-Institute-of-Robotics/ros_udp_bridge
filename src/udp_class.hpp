#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFF_SIZE 2048 
#define PORT 1153

class UDPReceive{
    int port;
    unsigned char buffer[BUFF_SIZE];
    struct sockaddr_in myaddr;
	struct sockaddr_in remaddr; 
    socklen_t addrlen;
    int recvlen;
	int server;
    public:
        UDPReceive(int port);
        void start();
};


