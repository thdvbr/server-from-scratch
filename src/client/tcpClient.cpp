#include "tcpClient.h"

TcpClient::TcpClient(std::string ipAddress, int port) : m_ipAddress(ipAddress), m_port(port) {}

void TcpClient::Run()
{
    char buf[MAX_BUFFER_SIZE];
    while (true)
    {
        int clientSocket = CreateClientSocket();
        if (clientSocket < 0)
        {
            break;
        }
        if (clientSocket != -1)
        {
            std::string userInput;
            do
            {
                // enter lines of text
                std::cout << "> ";
                getline(std::cin, userInput);

                // send to server
                int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
                if (sendResult < 0)
                {
                    std::cout << "Could not send to server!\r\n";
                    continue;
                }
                // wait for response
                memset(buf, 0, MAX_BUFFER_SIZE);
                int bytesReceived = recv(clientSocket, buf, MAX_BUFFER_SIZE, 0);
                if (bytesReceived < 0)
                {
                    std::cout << "There was an error getting response from server\r\n";
                }
                else
                {
                    std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
                }
            } while (true);
            close(clientSocket);
        }
    }
}

int TcpClient::CreateClientSocket()
{
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        return -1;
    }
    // Create a hint structure for the server we're connecting with
    int port = 54000;
    std::string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    // Connect to the server on the socket
    int connectResult = connect(clientSocket, (sockaddr *)&hint, sizeof(hint));
    if (connectResult < 0)
    {
        std::cerr << "Can't connect";
        return -1;
    }
    std::cout << "Successfully created client socket" << std::endl;
    return clientSocket;
}
