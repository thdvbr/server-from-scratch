// you need a header guard or pragma once, pragma once is not standard
// so I prefere header gurards even if pragma once is easier to use
// https://en.wikipedia.org/wiki/Include_guard
//#ifndef server_tcpListener_h_
//#define server_tcpListener_h_
#pragma once

#include <iostream>
#include <string>

constexpr std::size_t MAX_BUFFER_SIZE = 1024;

//Forward declaration of class
class TcpListener;

// // Callback to data received
//typedef void (*MessageReceivedHandler)(TcpListener *listener, int socketId, std::string msg);
// I prefer the modern `using` syntax:
using MessageReceivedHandler = void (*)(TcpListener *listener, int socketId, std::string msgRecieved, int length);

class TcpListener
{
public:
    // constructor
    TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler);

    void Send(int clientSocket, std::string msg, int length);

    // run the listener
    void Run();

protected:
    virtual void OnMessageReceived(int clientSocket, std::string msg, int length);

private:
    int CreateSocket();
    int WaitForConnection(int m_socket);

    std::string m_ipAddress; // IP Address server will run on
    int m_port;              // Port # for the web service
    MessageReceivedHandler MessageReceived;
};

// End of the header gurard
//#endif //server_tcpListener_h_