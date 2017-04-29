// file: echo_s.c
// authors: DY TD SW SA AK JA
// date: 04/27/2017
// purpose: CS 3376 - 502
// description: A server that communicates in the internet domain handling both TCP/UDP
// It echos the messages it receives back to the client, and sends a copy of that message to a log server
// Accepts up to 3 ports to listen on, requires user stipulate both log server IP (using -logip "IP")
// and log server port number (using -logport "portnum"), otherwise throws error message and quits

#include <server_functions.h>
#include <log_s.h>

//SW: Accepts up to 3 port numbers and forks a TCP/UDP server for each
int main(int argc, char *argv[])
{
	int pids[3] = {0};
	int status;
	//JA variable to store number of port numbers, SA: updated to reflect logport use
	int portNumbers = argc - 4; 
	//SA: index where logip ends
	int logipEnd = portNumbers + 2; 
	//JA variable for the log server ip, SA: updated to reflect logport use
	char* logip = argv[logipEnd - 1];
	//SA: var for the log server port num
	int logpo = atoi(argv[logipEnd + 1]); 

	//SW: Ensures correct usage
	//SA: changed valid num arguments yet again
	if (argc > 8 || argc < 6) 
	{ 
		//SA: explicated use case
		error("Correct usage: ./echo_s port1 port2 port3 -logip logip -logport logport\n"
			"(eg. ./echo_s 1000 1001 1002 -logip 10.24.36.33 -logport 8888)\n"
			"**USAGE EXPLICIT**: ordering options in other orders not supported"); 
		return 1;
	}

	//JA checking if logip argument was used
	if (strcmp(argv[portNumbers], "-logip")) error("Invalid use on -logpip");

	//SA: Check for logport option (which isn't optional ¯\_(ツ)_/¯ )
	if (strcmp(argv[logipEnd], "-logport")) error("Invalid use on -logport");

	//SW:if 3 port numbers given, start server three
	//JA changed argc to portNumbers  
	if (portNumbers > 3 && (pids[0] = fork()) == 0) //JA changed variable name to portNumbers.
		 //JA added logip to pass log server ip address, SA: added logpo
		startServer(atoi(argv[3]), echoResult_tcp, echoResult_udp, logip, logpo);
	//SW:if 2 port numbers given, start server two	
	else if (portNumbers > 2 && (pids[1] = fork()) == 0) 
		startServer(atoi(argv[2]), echoResult_tcp, echoResult_udp, logip, logpo); 
	//SW: start server one
	else if ((pids[2] = fork()) == 0)
		startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp, logip, logpo); 
	
	//AK: Special helper function; uses static variables to emulate a closure around logip in exitServer
	storeLogIP(0, logip);
	//AK: Special usage of exitServer; uses static variables to emulate a closure around logpo
	exitServer(-logpo);
	//AK: Previous two calls are to set up exitServer function to be used as a function pointer and give it access to logpo and logip
	signal(SIGINT, exitServer);

	for (int i = 0; i < 3; i++) {
		if (pids[i] != 0)
			waitpid(pids[i], &status, 0);
	}
    return 0; 
}
