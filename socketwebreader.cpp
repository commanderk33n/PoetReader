#include "socketwebreader.h"

SocketWebReader::SocketWebReader(char* host, ushort port, int* error)
{
#ifdef WIN32
    initWin(host, port);
#else
    initUnix(host, port);
#endif
}


int SocketWebReader::initUnix(char* host, ushort port)
{
#ifndef WIN32
    sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0)
    {

        return 2;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {

        return 3;
    }
#else
    return 4;
#endif
    return 0;
}

int SocketWebReader::initWin(char* host, ushort port)
{
#ifdef WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    sock = INVALID_SOCKET;
#else
    return 4;
#endif
    return 0;
}

std::iostream* SocketWebReader::GetStream(char* endpoint)
{
    char buffer[BUFFER_SIZE] = {0};
    int valread = 0;
    char *reguest = endpoint;//"GET /Quellen/fi/dichter_liste.txt\r\n";

    std::stringstream* ss = new std::stringstream() ;

    send(sock , reguest , std::strlen(reguest) , 0 );
    while(read( sock , buffer, BUFFER_SIZE) > 0)
    {
        ss->write(buffer, BUFFER_SIZE);
    }

    std::cout << std::endl;
    return ss;
}

