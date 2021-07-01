#ifndef SOCKETWEBREADER_H
#define SOCKETWEBREADER_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
typedef SOCKET Socket;
typedef PCSTR Port;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int Socket;
typedef ushort Port;
#endif





#define BUFFER_SIZE 1




class SocketWebReader
{
public:
    SocketWebReader(char* host, Port port, int* error = nullptr);
    ~SocketWebReader();

    std::iostream* GetStream(char* endpoint);

private:
    Socket sock;
    int initWin(char* host, Port port);
    int initUnix(char* host, Port port);

};

#endif // SOCKETWEBREADER_H
