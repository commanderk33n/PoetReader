#ifndef SOCKETWEBREADER_H
#define SOCKETWEBREADER_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
typedef SOCKET Socket;
typedef PCSTR Port;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


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
    SocketWebReader(std::string host, Port port, int* error = nullptr);
    ~SocketWebReader();

    std::iostream* GetStream(std::string endpoint);

private:
    Socket sock;
    int initWin(std::string host, Port port);
    int initUnix(std::string host, Port port);

};

#endif // SOCKETWEBREADER_H
