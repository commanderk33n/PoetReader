#include "socketwebreader.h"

SocketWebReader::SocketWebReader(std::string host, Port port, int* error)
{
#ifdef WIN32
    int err = initWin(host, port);
    if(error != nullptr)
        *error = err;
#else
    int err = initUnix(host, port);
    if(error != nullptr)
        *error = err;
#endif
}

SocketWebReader::~SocketWebReader()
{
#ifdef WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif

}


int SocketWebReader::initUnix(std::string host, Port port)
{
#ifndef WIN32
    sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((ushort)atoi(port));

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) != 1)
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

int SocketWebReader::initWin(std::string host, Port port)
{
#ifdef WIN32
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    sock = INVALID_SOCKET;

    if(iResult != 0)
        return 1;

    ZeroMemory( &hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    // Resolve the server address and port
    iResult = getaddrinfo(host.c_str(), port, &hints, &result);

    if(iResult != 0) {
        WSACleanup();
        return 2;
    }

    ptr = result;
    sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(sock == INVALID_SOCKET)
        return 3;

    iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
    if(iResult == SOCKET_ERROR) {
      closesocket(sock);
      sock = INVALID_SOCKET;
      return 4;

    }
    freeaddrinfo(result);

    if(sock == INVALID_SOCKET) {
        WSACleanup();
        return 3;
    }

#else
    return 10;
#endif
    return 0;
}

std::iostream* SocketWebReader::GetStream(std::string endpoint)
{
    char buffer[BUFFER_SIZE] = {0};
    int valread = 0;
    //char *request = endpoint;//"GET /Quellen/fi/dichter_liste.txt\r\n";
    std::stringstream* ss = new std::stringstream();

#ifdef WIN32

    if(send(sock, endpoint.c_str(), endpoint.length(), 0) == SOCKET_ERROR)
        return ss;

    do {
       valread = recv(sock, buffer, BUFFER_SIZE,0);
       if(valread > 0)
           ss->write(buffer, valread);

    } while (valread > 0);

#else

    if (send(sock , endpoint.c_str() , std::strlen(endpoint.c_str()) , 0 ) < 0)
        return ss;

    do {
       valread = read(sock, buffer, BUFFER_SIZE);
       if(valread > 0)
           ss->write(buffer, valread);

    } while (valread > 0);

#endif


    return ss;
}

