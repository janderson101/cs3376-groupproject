// file: log_s.h
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Log server that communicates with echo_s to log the messages echo_s receives
#ifndef LOG_S_H
#define LOG_S_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>

void error(const char*);

//TD: starts the log server (UDP) upon being called on in the server
int startLogServer(int);

//TD: handles zombies
void SigCatcher(int);

//SW: loops listens on "portno" and send message to function "writetofile"
void udp_loop(int);

//SW: function to write to file
//function accepts "buf", the message and ip address, and write to file "echo.log"
void writetofile(char[1024]);

#endif
