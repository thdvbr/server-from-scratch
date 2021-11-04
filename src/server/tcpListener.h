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

//Forward declaration of class
class TcpListener;

// // Callback to data received
typedef void (*MessageReceivedHandler)(TcpListener *listener, int socketId, std::string msg);

class TcpListener
{
public:
    // constructor
    TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler);

    void Send(int clientSocket, std::string msg);

    // run the listener
    void Run();

private:
    int CreateSocket();
    int WaitForConnection(int m_socket);

    std::string m_ipAddress; // IP Address server will run on
    int m_port;              // Port # for the web service
    MessageReceivedHandler MessageReceived;
};