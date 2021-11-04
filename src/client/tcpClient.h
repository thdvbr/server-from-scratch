#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#define MAX_BUFFER_SIZE (4096)

class TcpClient
{
public:
    TcpClient(std::string ipAddress, int port);
    void Run();

private:
    int CreateClientSocket();
    int m_port;
    std::string m_ipAddress;
};