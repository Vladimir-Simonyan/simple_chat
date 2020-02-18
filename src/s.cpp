// Server side C/C++ program to demonstrate Socket programming 
#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>

#define IP "127.0.0.1"
#define PORT 8080 

void * receiver(void * sock)
{
	char rbuffer[1024] = { 0 };
	while(read(*((int *)sock), rbuffer, 1024) > 0)
	{
		std::cout << "He: " << rbuffer << "\n";
		//std::cout << ">  ";  
	} 
	std::cout << "Connection failed \n";
	exit(-4);
	return 0;
}

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		std::cout << "socket failed"; 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		std::cout << "setsockopt"; 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		std::cout << "bind failed"; 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		std::cout << "listen"; 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
	{ 
		std::cout << "accept"; 
		exit(EXIT_FAILURE); 
	} 

	std::cout << "Connected \n";

	// RECV
	pthread_t recv_thread;
	if(pthread_create(&recv_thread, NULL, receiver, (void *)&new_socket) != 0)
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

		send(new_socket ,  sbuffer, strlen(sbuffer), 0); 
	}

	return 0; 
} 
