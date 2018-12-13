#include "udp_motor_send.hpp"

UDPSend::UDPSend(int port)
	: port(port)
{  
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);

	slen = sizeof(myaddr);
	count = 0;

    if ((server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		print_info("The socket can't be created\n"); 
	}

	if (bind(server, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
		print_info("Bind failed");
	}

	if (inet_aton(SERVER , &myaddr.sin_addr) == 0) {

		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	printf("Send packet from %s:%d\n", inet_ntoa(myaddr.sin_addr), ntohs(myaddr.sin_port));
}

void UDPSend::send(/*const std_msgs::String::ConstPtr& msg*/){

	while(1){

		if (sendto(server, motor1_0, sizeof(motor1_0) , 0 , (struct sockaddr *) &myaddr, slen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor2_0, sizeof(motor2_0) , 0 , (struct sockaddr *) &myaddr, slen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor1_1, sizeof(motor1_1) , 0 , (struct sockaddr *) &myaddr, slen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor2_1, sizeof(motor2_1) , 0 , (struct sockaddr *) &myaddr, slen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (count >= 10){
			exit(1);
		}
		else count ++; 
	}
}

void UDPSend::print_info(const char *info){
	perror(info);
	exit(1);
}

void UDPSend::receivefrom(){

    memset(buffer,'\0', BUFF_SIZE);
	if (recvfrom(server, buffer, BUFF_SIZE, 0, (struct sockaddr *) &myaddr, &addrlen) == -1) {
	    print_info("recvfrom()");
    }
	if (buffer[4] == 0) printf("Message received motor %u\n", buffer[2]);
	//else printf("%s\n",buffer);
}



int main(int argc, char **argv) {
	int port = 49160;
	ros::init(argc, argv, "udp_motor_node");
	UDPSend udp(port);
	udp.send();
	ros::spin();
	return 0;
}
