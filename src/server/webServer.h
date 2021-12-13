#pragma once

#include "tcpListener.h"

class WebServer : public TcpListener
{
public:
    WebServer(const char *ipAddress, int port) : TcpListener(ipAddress, port) {}

protected:
    virtual void OnMessageReceived(int clientSocket, std::string msg, int length);
};