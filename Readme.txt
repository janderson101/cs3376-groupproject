Semester Project, Second Deliverable
Due: 4/23/17

Authors (initials):
    Asad-ullah Khan  (AK)
    James Anserson (JA)
    Salman Anwer (SA)
    Tiffany Do (TD)
    Seong Ioi Wang (SW)
    Dylan Yu (DY)
    
Files in zip: obj/* (empty directory, for linking objects), src/* (source files), include/* (header files), Makefile, Readme.txt, echo.log

Purpose:
    Create a "echo_s" executable that accepts TCP/UDP messages and a "echo_c" executable that sends messages to this server. The server (echo_s) should then reply to the client with the same message it receives.
    echo_c is able to send messages using TCP or UDP based on the option passed to it. For example, "./client cs2 30000 udp" would connect the client to the host cs2 on port 30000 using the UDP protocol. 
    echo_s will then forward a record of the messages it receives to the "log_s" server. log_s will then log this information in a log file "echo.log"
    log_s's port number is centrally defined in logpo.h 
    
Description:
    Extract files and run makefile. Make sure to use "netstat -an" to find an open port number (if ports are already being used, the server will consider it a user error and fail). Issue the kill sequence (Ctr-c) on the command line once the program is running to terminate the server safely. 
