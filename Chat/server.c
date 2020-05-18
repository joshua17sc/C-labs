#include <stdio.h>
#include <stdlib.h> //strlen
#include <string.h> //strlen
#include <unistd.h> //write
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //inet_addr
#include <pthread.h> //for threading, link with lpthread

void *connection_handler(void *);

//This will print our error messages and end our program
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

//Creates a socket, binds, listens, accepts, reads and writes, then closes
int main(int argc, char *argv[])
{
	
	//Initiates our variables
	int sockfd , newsockfd , n, *new_sock;
	char *message;
	struct sockaddr_in server, client;
	socklen_t clilen;
	
	//Creates socket
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(sockfd <0)
	{
		error("Error opening Socket.");
	}
		
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	//Bind
	if(bind(sockfd , (struct sockaddr *) &server , sizeof(server)) <0)
	{
		error("Binding Failed.");
	}
	puts("Bind complete");
	
	//Listen	
	listen(sockfd , 5);
	
	//Accept incoming connection
	puts("Waiting for incoming connections...");
	clilen = sizeof(client);
	while( (newsockfd = accept(sockfd , (struct sockaddr *)&client , (socklen_t*)&clilen)) )
	{
		puts("Connection accepted");
	
		//Welcome client
		message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
		write(newsockfd , message , strlen(message));
	
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = newsockfd;
		
		if( pthread_create( &sniffer_thread , NULL , connection_handler , (void*) new_sock) <0)
		{
			error("Could not create thread.");
		}
			
		//Now join the thread , so that we don't terminate before the thread
		pthread_join(sniffer_thread , NULL);
		puts("Handler assigned");
	}
	
	if(newsockfd < 0)
	{
		error("Error on Accept");
	}
	return 0;
}

// This will handle connections for each client
void *connection_handler(void *sockfd)
{
	//Get the socket descriptor
	int sock = *(int*)sockfd;
	int read_size;
	char *message, client_message[255];
	
	//Send some messages to the client
	message = "Greetings! I am your connection handler.\n";
	write(sock , message , strlen(message));
	
	message = "Now type something and I shall repeat what you type.\n";
	write(sock , message , strlen(message));
	
	//Receive a message from client
	while( (read_size = recv(sock , client_message , 255 , 0)) >0 )
	{
		//Send the message back to the client
		write(sock , client_message , strlen(client_message));
	}
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		error("Failed to receive");
	}
	
	//Free the socket pointer
	free(sockfd);
	
	return 0;
}
