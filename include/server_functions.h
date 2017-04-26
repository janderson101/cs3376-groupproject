// file: server_functions.h
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Contains functions necessary for the echo server
#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>

//SA: Issued when a system call fails. Displays error message and aborts
void error(const char*);

//TD: initializes the TCP and UDP sockets
void intializeSockets(int*, int*);

//SA: Handles initializing the sockaddr_in structure with the port# passed in 
void initializeAddrStruct(struct sockaddr_in*, int);

//SA/JA: Binds all addresses to their respective sockets. Throws error if binding fails
void bindAll(int*, int*, struct sockaddr_in*); 

//SA/JA: First opens a UDP socket and then handles initializing the socket address structure 
// with the port# passed in
void setupLogServer(int *sockudp, struct sockaddr_in *serv_addr, int portno); 

//Echos back a response upon receiving a UDP message -DY
int echoResult_udp(char buf[256], int sockfd, struct sockaddr_in response);

//Echos back a response upon receiving a TCP message -DY
int echoResult_tcp(char buf[256], int sockfd, struct sockaddr_in response);

//SA: Handles starting the server (utilizing both TCP and UDP). Keeps server alive until a "TERM" command is issued
// then handles safe termination of all server resources 	
int startServer(int, int callback_tcp(char[256], int, struct sockaddr_in),
				int callback_udp(char[256], int, struct sockaddr_in));

#endif
