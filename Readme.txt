Semester Project, Third Deliverable
Due: 4/30/17

Authors (initials) and Githubs:
    James Anderson (JA)      -    janderson101
    Salman Anwer (SA)        -    BigBossAnwer
    Tiffany Do (TD)          -    zyrcant
	Asad-ullah Khan (AK)     -    Kh4n
    Seong Ioi Wang (SW)      -    seongioi
    Dylan Yu (DY)            -    JonahFarc

Github: https://github.com/janderson101/cs3376-groupproject/

Files in zip: obj/* (empty directory, for linking objects), src/* (source files), include/* (header files), Makefile, Readme.txt, echo.log

Purpose:
    Create a "echo_s" executable that accepts TCP/UDP messages and a "echo_c" executable that sends messages to this server. The server (echo_s) should then reply to the client with the same message it receives.
    echo_c is able to send messages using TCP or UDP based on the option passed to it. For example, "./client cs2 30000 udp" would connect the client to the host cs2 on port 30000 using the UDP protocol. 
    echo_s will then forward a record of the messages it receives to the "log_s" server. log_s will then log this information in a log file "echo.log"
    echo_s will take up to 3 port numbers, a log ip address, and a log port. The format will be "./echo_s port1 [port2 port3] -logip <addr> -logport <port>"
    log_s will take a log port. The format is "./log_s -port <port>".
    
Description:
    Extract files and run makefile. Make sure to use "netstat -an" to find an open port number (if ports are already being used, the server will consider it a user error and fail). Issue the kill sequence (Ctr-c) on the command line once the program is running to terminate the server safely. 

Changes:
    JA: Added parameter "-logip <log>" to echo_s. Allows echo_s to log to a log server on a different IP address.
	SA: Added parameter "-logport <port>" to echo_s. Provides the port on the given IP address to send information to.
	TD: Added parameter "-port <port>" to log_s. Allows log_s to listen on the given port.
	AK: Closed log server upon closing the echo server.
	SW: Logged message when echo server tells the log server to close.
