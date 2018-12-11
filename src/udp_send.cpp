#include "udp_send.hpp"

UDPSend::UDPSend(int port)
	: port(port)
{  
	sub = n.subscribe("udp_send", 10, UDPSend::send);
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);
    
	my_message = "\nluciana\n";
    if ((server = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("The socket can't be created\n"); 
	}
}

void UDPSend::send(const std_msgs::String::ConstPtr& msg){

    ROS_INFO("I heard: [%s]", msg->data.c_str());

	if (sendto(server, my_message, strlen(my_message), 0, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("sendto failed");
	}
}

int main(int argc, char **argv) {
	int port = 1153;
	ros::init(argc, argv, "udp_comm_node");
	UDPSend udp(1153);
	ros::spin();
	return 0;
}