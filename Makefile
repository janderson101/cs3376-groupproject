#Makefile for Semester Project Deliverable 2
#Two-step compilation
#Created 4/23/2017

SHELL       = /bin/sh
OBJS_LOG    = $(patsubst %.o, obj/%.o, log_s.o)
OBJS_SERVER = $(patsubst %.o, obj/%.o, echo_s.o server_functions.o)
OBJS_CLIENT = $(patsubst %.o, obj/%.o, echo_c.o client_functions.o)
LDFLAGS     = -o 
CPPFLAGS    = -Wall -g -std=gnu99 -Iinclude -c
CC          = gcc

all:     echo_s echo_c log_s

echo_s:  $(OBJS_SERVER)
	$(CC) $(LDFLAGS) echo_s $(OBJS_SERVER)

echo_c:  $(OBJS_CLIENT)
	$(CC) $(LDFLAGS) echo_c $(OBJS_CLIENT)	

log_s:   $(OBJS_LOG)	
	$(CC) $(LDFLAGS) log_s  $(OBJS_LOG)	

obj/%.o: src/%.c 
	$(CC) $(CPPFLAGS) -o $@ $<

clean:
	rm -f core echo_s echo_c log_s obj/*.o
