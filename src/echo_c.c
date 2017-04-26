// file: echo_c.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: A simple client in the internet domain using TCP/UDP
// The hostname, port number, and protocol are passed as arguments

#include <client_functions.h>

int main(int argc, char *argv[])
{
  	//TD: checks to make sure user has given all arguments
	if (argc != 4)
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");
	//TD: checks for TCP or UDP and sends to appropriate method
	if (strcmp(argv[3], "udp") == 0) 
		clientConnect_udp(argv[1], atoi(argv[2]), sendMessageToServer_udp);
	else if (strcmp(argv[3], "tcp") == 0)
		clientConnect_tcp(argv[1], atoi(argv[2]), sendMessageToServer_tcp);
	else
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");
    return 0;
}
