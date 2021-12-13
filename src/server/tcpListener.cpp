#include "tcpListener.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

// constructor
TcpListener::TcpListener(std::string ipAddress, int port)
    : m_ipAddress(ipAddress), m_port(port){};

void TcpListener::Send(int clientSocket, std::string msg, int length)
{
    // send(clientSocket,buffer,size,flag)
    send(clientSocket, msg.c_str(), length, 0);
}

void TcpListener::Run()
{
    // while loop: accept and echo message back to client
    char buf[MAX_BUFFER_SIZE];

    // Create a listening socket
    int listeningSocket = CreateSocket();
    if (listeningSocket < 0)
    {
        // throw std::runtime_error("cant create listener socket");
        return;
    }

    while (true)
    {
        // wait for client to send data
        int clientSocket = WaitForConnection(listeningSocket);

        // create a new thread that executes the client connection handling code.
        if (clientSocket != -1)
        {
            int bytesReceived = 0;
            do
            {
                // clear out the memory
                memset(buf, 0, MAX_BUFFER_SIZE);
                // receive into that buffer
                bytesReceived = recv(clientSocket, buf, MAX_BUFFER_SIZE, 0);
                if (bytesReceived < 0)
                {
                    std::cerr << "There was a connection issue" << std::endl;
                    break;
                }
                if (bytesReceived == 0)
                {
                    std::cout << "The client disconnected" << std::endl;
                    break;
                }
                //if bytesReceived > 0
                // Echo message back to client
                if (bytesReceived > 0)
                // else
                {

                    std::cout << "Received: " << std::string(buf, 0, bytesReceived) << std::endl;
                    // MessageReceived(this, clientSocket, std::string(buf, 0, bytesReceived), bytesReceived);
                    OnMessageReceived(clientSocket, std::string(buf, 0, bytesReceived), bytesReceived);
                }
            } while (bytesReceived > 0);
            // if the client disconnects, closes client socket and go to the top, create new socket
            close(clientSocket);
        }
    }

    close(listeningSocket);
}

int TcpListener::CreateSocket()
{
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // socket(domain, type, protocol)
    if (serverSocket < 0)
    {
        std::cerr << "Can't create a socket!";
        return -1;
    }
    // Bind an ip address and port to the socket
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);                 // htons = host to network short - converts short int (e,g. port) to network representation
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // (version for the internet, any address, buffer)

    if (bind(serverSocket, (struct sockaddr *)&hint, sizeof(hint)) < 0)
    {
        std::cerr << "Can't bind to IP/port";
        return -1;
    }
    // Mark the socket for listening in
    if (listen(serverSocket, SOMAXCONN) < 0)
    {
        std::cerr << "Can't listen!";
        return -1;
    }
    return serverSocket;
}

int TcpListener::WaitForConnection(int m_socket)
{
    // Accept a call
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSocket = accept(m_socket, (sockaddr *)&client, &clientSize);

    if (clientSocket < 0)
    {
        std::cerr << "Problem with client connecting!";
        return -1;
    }
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);
    // converts socket addr to host and service
    int result = getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if (result)
    {
        std::cout << host << " connected on " << svc << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    }
    return clientSocket;
}

void TcpListener::OnMessageReceived(int clientSocket, std::string msg, int length)
{
    Send(clientSocket, msg, length);
}

// //---------------------------------------------------------------------------------
// //Example code for function pointers, you do not need the code for anything
// void func(int a) {
//     // ...
// }

// using fun_type = void (int);
// using fun_ptr_type = void (*)(int);

// void test() {
//     int a= 1;

//     int* ap = &a;
//     fun_type* fp = &func;
//     fun_ptr_type fp2 = &func;
// }
// //---------------------------------------------------------------------------------