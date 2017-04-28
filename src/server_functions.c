// file: server_functions.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Contains functions necessary for the echo server

#include <server_functions.h>

//SA: Issued when a system call fails. Displays error message and aborts
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//TD: initializes the TCP and UDP sockets
void intializeSockets(int *socktcp, int *sockudp) 
{
	if ((*socktcp = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("ERROR opening socket");
	if ((*sockudp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		error("ERROR opening socket");
}

//SA: Handles initializing the sockaddr_in structure with the port# passed in 
void initializeAddrStruct(struct sockaddr_in *serv_addr, int portno) 
{
	bzero((char *) serv_addr, sizeof(*serv_addr));
	(*serv_addr).sin_family = AF_INET;
	(*serv_addr).sin_addr.s_addr = INADDR_ANY;
	(*serv_addr).sin_port = htons(portno);
}

//SA/JA: Binds all addresses to their respective sockets. Throws error if binding fails
void bindAll(int *sockfd_tcp, int *sockfd_udp, struct sockaddr_in *serv_addr) 
{
	if (bind(*sockfd_tcp, (struct sockaddr *) serv_addr,
		  sizeof(*serv_addr)) < 0) 
		  error("ERROR on binding");
	if (bind(*sockfd_udp, (struct sockaddr *) serv_addr,
		  sizeof(*serv_addr)) < 0) 
		  error("ERROR on binding");
}

//SA/JA: First opens a UDP socket and then handles initializing the socket address structure with the port# passed in
//JA added logip for the log server ip address 
void setupLogServer(int *sockudp, struct sockaddr_in *serv_addr, int portno, char* logip)
{
	if ((*sockudp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		error("ERROR opening socket");
	bzero((char *) serv_addr, sizeof(*serv_addr));
	(*serv_addr).sin_family = AF_INET;
	//JA changed to set up based on user input for ip address
	(*serv_addr).sin_addr.s_addr = inet_addr(logip);
	(*serv_addr).sin_port = htons(portno);
}

//Echos back a response upon receiving a UDP message -DY
//JA added logip to pass log server ip address, SA: Added logpo param
int echoResult_udp(char buf[256], int sockfd, struct sockaddr_in response, char* logip, int logpo) 
{
	int sockfd_log;
	struct sockaddr_in log_addr;
	//JA added logip to pass log server ip address, SA: portno = logpo instead of LOGPORT
	setupLogServer(&sockfd_log, &log_addr, logpo, logip); 
	char loginfo[256] = {0};
	socklen_t clilen = sizeof(struct sockaddr_in);

	printf("\nReceived via UDP: %s", buf);
	while (1) 
	{
		bzero(loginfo, 256);
		//SW: Adds beginning quote to message
		strcpy(loginfo, "\""); 
		//SW: Appends message received via UDP
		strncat(loginfo, buf, strlen(buf) - 1); 
		//SW: Adds end quote to message
		strcat(loginfo, "\" recieved from "); 
		//SW: Appends IP address
		strcat(loginfo, inet_ntoa(response.sin_addr));
		strcat(loginfo, "\n");
		printf("Sending message back and logging...\n");
		if (sendto(sockfd_log, loginfo, strlen(loginfo), 0, (struct sockaddr*)&log_addr, clilen) < 0)
			error("ERROR sendto");
		if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&response, clilen) < 0)
			error("ERROR sendto");
		bzero(buf, 256);
		if (recvfrom(sockfd, buf, 256, 0, (struct sockaddr*)&response, &clilen) < 0)
			error("ERROR recvfrom");
		printf("\nRecieved via UDP: %s", buf);
	}
	close(sockfd_log);
	return 0;
}

//Echos back a response upon receiving a TCP message -DY
//JA added logip to pass the log server ip address
int echoResult_tcp(char buf[256], int sockfd, struct sockaddr_in response, char* logip, int logpo) 
{
	int sockfd_log;
	struct sockaddr_in log_addr;
	//JA added logip to pass the log server ip address, SA: portno = logpo instead of LOGPORT
	setupLogServer(&sockfd_log, &log_addr, logpo, logip); 

	char loginfo[256] = {0};

	printf("\nReceived via TCP: %s", buf);
	while (1) 
	{
		bzero(loginfo, 256);
		//SW: Adds beginning quote to message
		strcpy(loginfo, "\""); 
		//SW: append message received via TCP
		strncat(loginfo, buf, strlen(buf) - 1);
		//SW: Adds end quote to message
		strcat(loginfo, "\" recieved from "); 
		//SW: Appends IP address
		strcat(loginfo, inet_ntoa(response.sin_addr));
		strcat(loginfo, "\n");
		printf("Sending message back and logging...\n");
		if (sendto(sockfd_log, loginfo, strlen(loginfo), 0, (struct sockaddr*)&log_addr, sizeof(struct sockaddr_in)) < 0)
			error("ERROR sendto");
		if (send(sockfd, buf, strlen(buf), 0) < 0)
			error("ERROR send");
		bzero(buf, 256);
		int response = recv(sockfd, buf, 256, 0);
		if (response < 0)
			error("ERROR recv");
		else if (response == 0)
			break;
		printf("\nReceived via TCP: %s", buf);
	}
	close(sockfd_log);
	return 0;
}

//SA: Handles starting the server (utilizing both TCP and UDP). 
//JA added logip to pass ip address for log server, SA: Added logpo param
int startServer(int portno, int callback_tcp(char[256], int, struct sockaddr_in, char* logip, int logpo),
				int callback_udp(char[256], int, struct sockaddr_in, char* logip, int logpo), char* logip, int logpo) 
{
	int sockfd_tcp, newsockfd_tcp, sockfd_udp;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	clilen = sizeof(struct sockaddr_in);
	
	intializeSockets(&sockfd_tcp, &sockfd_udp);

	initializeAddrStruct(&serv_addr, portno);
	
	bindAll(&sockfd_tcp, &sockfd_udp, &serv_addr);

	if (fork() == 0) 
	{
		listen(sockfd_tcp, 5);
		do 
		{	
			if ((newsockfd_tcp = accept(sockfd_tcp, (struct sockaddr*) &cli_addr, &clilen)) < 0)
				error("ERROR on accept");
			bzero(buffer, 256);
			if (fork() == 0) 
			{
				if(recv(newsockfd_tcp, buffer, 256, 0) < 0)
					error("ERROR reading from socket");
				//JA added logip to pass log server ip address, , SA: added logpo
				callback_tcp(buffer, newsockfd_tcp, cli_addr, logip, logpo); 
				exit(0);
			}
		} while (1);
	}
	else
	{
		do 
		{
			bzero(buffer, 256);
			if (recvfrom(sockfd_udp, buffer, 256, 0, (struct sockaddr*) &serv_addr, &clilen) < 0)
				error("recvfrom");
			if (fork() == 0) 
			{
				//JA added logip to pass log server ip address, , SA: added logpo
				callback_udp(buffer, sockfd_udp, serv_addr, logip, logpo); 
				exit(0);
			}
		} while (1);
	}
	return 0;
}
