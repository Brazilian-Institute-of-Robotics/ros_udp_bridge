#include "ros/ros.h"

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>

//#include <std_msgs/String.h>

#define BUFF_SIZE 512 // BUFLEN 
#define SERVER "10.88.119.102"

const unsigned char motor1_0[9] = {0xff, 0xff, 0x01, 0x05, 0x03, 0x1e, 0x00, 0x00, 0xd8};
const unsigned char motor1_1[9] = {0xff, 0xff, 0x01, 0x05, 0x03, 0x1e, 0xff, 0x0f, 0xca};
const unsigned char motor2_0[9] = {0xff, 0xff, 0x02, 0x05, 0x03, 0x1e, 0x00, 0x00, 0xd7};
const unsigned char motor2_1[9] = {0xff, 0xff, 0x02, 0x05, 0x03, 0x1e, 0xff, 0x0f, 0xc9};

class UDPSend{
    unsigned char buffer[BUFF_SIZE]; // era unsigned char
    int port, server, count, slen;
    struct sockaddr_in myaddr;
    socklen_t addrlen;

    //std_msgs::String msg_received;
    //std_msgs::String msg_toSend;
    char message[BUFF_SIZE];

    public:
        ros::NodeHandle n;
        //ros::Subscriber sub;
        //ros::Publisher pub;

        UDPSend(int port);
        void send(/*const std_msgs::String::ConstPtr& msg*/);
        void print_info(const char *info);
        void receivefrom();
};


