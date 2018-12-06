#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "ros/ros.h"
#include "std_msgs/String"

#include 

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
    ros::NodeHandle n;
    ros::Publisher pub;
    public:
        UDPReceive(int port);
        void start();
};


