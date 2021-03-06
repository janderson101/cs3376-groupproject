// file: log_s.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Log server that communicates with echo_s to log the messages echo_s receives

#include <log_s.h>

//TD: Issued when system call fails. Displays error message.
void error(const char *msg)
{
  perror(msg);
  exit(1);
}

//TD: starts the log server (UDP) upon being called on in the server
int startLogServer(int portno)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//TD: prints error if it cannot open the UDP socket
	if(sockfd < 0) error("ERROR OPENING UDP SOCKET FOR LOG SERVER");
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	  error("ERROR BINDIN UDP FOR LOG SERVER");
	//TD: continuous loop that will receive UDP messages
	udp_loop(sockfd);
	close(sockfd);
	return 0;
}

//SW: loops listens on "portno" and send message to function "writetofile"
void udp_loop(int udp_sockfd)
{
	int n;
	struct sockaddr_in from;
	socklen_t fromlen;
	char buf[1024];
	fromlen = sizeof(struct sockaddr_in);
	while(1)
	{
	   bzero(buf, 1024);
	   n = recvfrom(udp_sockfd,buf,1024,0,(struct sockaddr *)&from,&fromlen);
	   if(n<0) exit(0);
	   writetofile(buf, udp_sockfd);//passes the message from echo_s and the socket file desc. in case the message is the shutdown message
	}
}

//SW: function to write to file
//function accepts "buf", the message and ip address, and write to file "echo.log"
//int sockfd is the socket file descr. for the server. needed if shut down message is send
void writetofile(char buf[1024], int sockfd)
{
	FILE *fw;
	//SW: makes echo.log it if does not exist, append to it if it does
	fw = fopen("echo.log", "a"); 
	time_t ti = time(NULL);
	//SW: get the time 
	struct tm t = *localtime(&ti); 
	if(strcmp(buf,"echo_s is stopping") == 0){// if message is the term message, log it and stop server
		printf("log server recieve shutdown command from echo_s, closing now\n");
		fprintf(fw, "%s\n", buf); //SW: write exit message
		close(sockfd);
	} else {//log all messages send to echo_s
		fprintf(fw,"%d-%d-%d %d:%d:%d\t%s\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, buf); //SW: write date, message, and ipaddress to file
	}
	//SW: save file
	fclose(fw); 
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
      error("Correct usage: ./log_s -port portnum");
      return 1;
    }
    //TD: Check that the user is using -port, which is not optional
    if(strcmp(argv[1], "-port")) error("Invalid use on -port");
    int logpo = atoi(argv[2]);
    startLogServer(logpo);
    return 0; 
}
