#include "ros/ros.h"

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <std_msgs/Char.h>
#include <sstream>

#define BUFF_SIZE 2048 

class UDPReceive{
    int port;
    unsigned char buffer[BUFF_SIZE];
    struct sockaddr_in myaddr;
	struct sockaddr_in remaddr; 
    socklen_t addrlen;
    int recvlen;
	int server;
    std_msgs::Char msg;

    public:
        ros::NodeHandle n;
        ros::Publisher pub;
        UDPReceive(int port);
        void start();
};


