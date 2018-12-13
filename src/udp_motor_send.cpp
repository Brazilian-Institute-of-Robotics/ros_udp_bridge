#include "udp_motor_send.hpp"

UDPSend::UDPSend(int port)
	: port(port)
{  

	int i=0;
	for(auto x:{0xff, 0xff, 0x01, 0x05, 0x03, 0x1e, 0x00, 0x00, 0xd8}){
		motor1_0[i]=x;
		i++;
	}

	i=0;

	for(auto x:{0xff, 0xff, 0x01, 0x05, 0x03, 0x1e, 0xff, 0x0f, 0xca}){
		motor1_1[i]=x;
		i++;
	}

	i=0;

	for(auto x:{0xff, 0xff, 0x02, 0x05, 0x03, 0x1e, 0x00, 0x00, 0xd7}){
		motor2_0[i]=x;
		i++;
	}

	i=0;

	for(auto x:{0xff, 0xff, 0x02, 0x05, 0x03, 0x1e, 0xff, 0x0f, 0xc9}){
		motor2_1[i]=x;
		i++;
	}

	//sub = n.subscribe("chatter", 1, &UDPSend::send, this);
	//pub = n.advertise<std_msgs::String>("udp_message", 100);
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	//myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
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

		if (sendto(server, motor1_0, sizeof(motor1_0) , 0 , (struct sockaddr *) &myaddr, addrlen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor2_0, sizeof(motor2_0) , 0 , (struct sockaddr *) &myaddr, addrlen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor1_1, sizeof(motor1_1) , 0 , (struct sockaddr *) &myaddr, addrlen)==-1) { print_info("sendto()"); }
		receivefrom();

		if (sendto(server, motor2_1, sizeof(motor2_1) , 0 , (struct sockaddr *) &myaddr, addrlen)==-1) { print_info("sendto()"); }
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
	else puts(buffer);
}



int main(int argc, char **argv) {
	int port = 1153;
	//ros::init(argc, argv, "udp_comm_node");
	UDPSend udp(port);
	udp.send();
	//ros::spin();
	return 0;
}