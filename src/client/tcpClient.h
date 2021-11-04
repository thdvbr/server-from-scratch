#pragma once

#include <iostream>
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