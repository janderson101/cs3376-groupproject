// file: client_functions.h
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: contains functions necessary for the client
#ifndef CLIENT_FUNCTION_H
#define CLIENT_FUNCTION_H

#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//SA: Issued when a system call fails. Displays error message and aborts
void error(const char*);

//Sends messages to the server using TCP until terminated -DY
void sendMessageToServer_tcp(int);

//Sends messages to the server using UDP until terminated -DY
void sendMessageToServer_udp(int, struct sockaddr_in);

//TD: connects the client for TCP
int clientConnect_tcp(char*, int, void callback(int));

//SA: Handles UDP client connections. Connects to the port# passed in
int clientConnect_udp(char*, int, void callback(int, struct sockaddr_in));

#endif
