#include "ros/ros.h"

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>

#include <std_msgs/String.h>

#define BUFF_SIZE 512 // BUFLEN 

class UDPSend{
    char buffer[BUFF_SIZE]; // era unsigned char
    int port, server, count, slen;
    struct sockaddr_in myaddr;
    socklen_t addrlen;

    std_msgs::String msg_received;
    std_msgs::String msg_toSend;
    char message[BUFF_SIZE];

    public:
        ros::NodeHandle n;
        ros::Subscriber sub;
        ros::Publisher pub;

        unsigned char motor1_0[9];
        unsigned char motor1_1[9];
        unsigned char motor2_0[9];
        unsigned char motor2_1[9];

        UDPSend(int port);
        void send(/*const std_msgs::String::ConstPtr& msg*/);
        void print_info(const char *info);
        void receivefrom();
};


