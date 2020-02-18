// Client side C/C++ program to demonstrate Socket programming 
#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h>

#define IP 		"127.0.0.1"
#define PORT 	8080 

void * receiver(void * sock)
{
	char rbuffer[1024] = { 0 };
	int pix;
	while((pix = read(*((int *)sock), rbuffer, 1024)) > 0)
	{
		rbuffer[pix] = '\0';
		std::cout << "He: " << rbuffer << std::endl;
		//std::cout << ">  "; 
	} 
	std::cout << "Connection failed \n";
	exit(-4);
	return 0;
}

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	//char *hello = "Hello from client\n\n"; 
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		std::cout << "\n Socket creation error \n"; 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, IP, &serv_addr.sin_addr)<=0) 
	{ 
		std::cout << "\nInvalid address/ Address not supported \n"; 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		std::cout << "\nConnection Failed \n"; 
		return -1; 
	} 

	std::cout << "Connected \n";

	// RECV
	pthread_t recv_thread;
	if(pthread_create(&recv_thread, NULL, receiver, (void *)&sock) != 0)
	{
		std::cerr << "Cannot create receiver \n";
		exit(-1);
	}


	// SEND
	char sbuffer[1024] = { 0 }; 
	while(true)
	{
		//std::cout << ">  ";
		std::cin.getline(sbuffer, sizeof(sbuffer));

		send(sock ,  sbuffer, strlen(sbuffer), 0); 
	}
	
	return 0; 
} 
