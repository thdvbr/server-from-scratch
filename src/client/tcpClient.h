#pragma once

#include <iostream>
#include <string>

#define MAX_BUFFER_SIZE (4096)

class TcpClient
{
public:
    TcpClient(const char *ipAddress, int port);
    void Run();

private:
    int CreateClientSocket();
    int m_port;
    const char *m_ipAddress;
};