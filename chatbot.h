#ifndef CHATBOT_H
#define CHATBOT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int sock;

void    connectToServer(const char *host, int port);
void    disconnect();

void    sendToServer(string m);
void    pingpong(string m);
void    botIdentify(string nick, string user, string pw);
void    botSkills(string m);

void    botLoop();

#endif
