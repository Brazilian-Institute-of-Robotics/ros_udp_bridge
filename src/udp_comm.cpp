#include "udp_comm.hpp"

UDPReceive::UDPReceive(int port)
	: port(port)
{  
	pub = n.advertise<std_msgs::String>("udp_message", 100);
    
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);
    
    if ((server = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("The socket can't be created\n"); 
	}
	
	if (bind(server, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("Bind failed");
	}

}

void UDPReceive::start(){

    while(1) {
		printf("Waiting on port %d\n", port);
		recvlen = recvfrom(server, buffer, BUFF_SIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		printf("%d bytes received\n", recvlen);
		if (recvlen > 0) {
			buffer[recvlen] = 0; 
			printf("received message: %s\n", buffer);
			ss << buffer;
			msg.data = ss.str();
			pub.publish(msg);		
		} 
	} 

}

int main(int argc, char **argv) {
	int port = 1152;
	ros::init(argc, argv, "udp_comm_node");
	printf("\nport: %d",port);
	UDPReceive udp(1152);
	udp.start();
	ros::spin();
	return 0;
}