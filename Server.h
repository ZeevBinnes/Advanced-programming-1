/*
 * server.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Server.h"
#include "commands.h"
#include "CLI.h"


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


class socketIO : public DefaultIO {
    int client;
public:
    socketIO(int client);
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
};


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int client){
        socketIO socket_io = socketIO(client);
        CLI cli(&socket_io);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in
    int clientLimit = 3;
    sockaddr_in address;
    volatile bool run;



public:
    int fd;
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
