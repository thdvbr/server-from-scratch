#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main()
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        return 1;
    }
    // Create a hint structure for the server we're connecting with
    int port = 54000;
    std::string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to the server on the socket
    int connectResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connectResult < 0)
    {
        return 1;
    }
    char buf[4096];
    std::string userInput;

    do
    { // enter lines of text
        std::cout << "> ";
        getline(std::cin, userInput);

        // send to server
        // TODO: What is buffer?
        int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendResult < 0)
        {
            std::cout << "Could not send to server!\r\n";
            continue;
        }

        // Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived < 0)
        {
            std::cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //display response
            std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
        }

    } while (true);

    // close socket
    close(sock);

    return 0;
}