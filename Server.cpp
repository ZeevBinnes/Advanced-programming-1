/*
 * server.cpp
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#include <sys/socket.h>
#include "Server.h"
#include<signal.h>
#include <iomanip>


Server::Server(int port)throw (const char*) {
    run = true;
    fd = socket(AF_INET, SOCK_STREAM,0);
    if (fd < 0) {
        throw "socket failed";
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw "bind failed";
    }

    if (listen(fd, clientLimit) < 0) {
        throw "listen failed";
    }
}




void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this](){
        while (run) {
            if (clients < clientLimit) {
                new thread([&ch, this]() {
                socklen_t addSize = sizeof(address);
                int clientID = accept(fd, (struct sockaddr*)&address, &addSize);;
                if (clientID < 0) {
                     throw "accept failed";
                } else {

                        clients++;
                        ch.handle(clientID);
                        close(clientID);
                        clients--;
                }});
            }
        }
        close(fd);
    });
}


void Server::stop(){
    run = false;
	t->join(); // do not delete this!
}

Server::~Server() {
    //
}

socketIO::socketIO(int client){
    this->client = client;
}


string socketIO:: read() {
    char c;
    string input = "";
    recv(client,&c,sizeof(char),0);
    while(c!='\n'){
        input+=c;
        recv(client,&c,sizeof(char),0);
    }
    return input;
}

void socketIO:: write(string text) {
        int n = text.size();
        const char* output = text.c_str();
        send(client, output, n,0);
}
void socketIO:: write(float f) {
        stringstream stream;
        stream << f;
        write(stream.str());
}
void socketIO:: read(float* f) {
        recv(client, f, sizeof(float), 0);
    }


