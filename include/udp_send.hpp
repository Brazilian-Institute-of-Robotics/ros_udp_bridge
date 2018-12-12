#include "ros/ros.h"

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>

#include <std_msgs/String.h>

#define BUFF_SIZE 2048 

class UDPSend{
    int port;
    struct sockaddr_in myaddr;
    socklen_t addrlen;
	int server;
    std_msgs::String msg;

    public:
        ros::NodeHandle n;
        ros::Subscriber sub;
        UDPSend(int port);
        void send(const std_msgs::String::ConstPtr& msg);
};


