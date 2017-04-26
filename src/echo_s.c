// file: echo_s.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: A server that communicates in the internet domain handling both TCP/UDP
// It echos the messages it receives back to the client, and sends a copy of that message to a log server
// Accepts up to 3 ports to listen on

#include <server_functions.h>
#include <log_s.h>
#include <logpo.h>

//SW: Accepts up to 3 port numbers and forks a TCP/UDP server for each
int main(int argc, char *argv[])
{
	int pids[3] = {0};
	int status;
	//SW: Ensures correct usage
	if (argc > 4 || argc < 2) 
	{ 
		error("Please provide up to 3 ports to monitor like so: ./server port1 port2 port3 (eg. ./server 1000, 1001, 1002)");
		return 1;
	}
	//SW:if 3 port numbers given, start server three 
	else if (argc > 3 && (pids[0] = fork()) == 0) 
		startServer(atoi(argv[3]), echoResult_tcp, echoResult_udp);
	//SW:if 2 port numbers given, start server two
	else if (argc > 2 && (pids[1] = fork()) == 0) 
		startServer(atoi(argv[2]), echoResult_tcp, echoResult_udp);
	//SW: start server one
	else if ((pids[2] = fork()) == 0)
		startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp);

	for (int i = 0; i < 3; i++) {
		if (pids[i] != 0)
			waitpid(pids[i], &status, 0);
	}
    return 0; 
}
