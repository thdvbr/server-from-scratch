#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <streambuf>
#include <iterator>
#include <vector>
#include "webServer.h"

void WebServer::OnMessageReceived(int clientSocket, std::string msg, int length)
{
    // GET /index.html  HTTP/1.1

    // Parse out the document requested
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>()); // vectorize the string
    std::string htmlFile = "/index.html";
    std::string content = "<h1>404 Not Found</h1>";
    int statusCode = 404;

    if (parsed.size() >= 3 || parsed[0] == "GET")
    {
        htmlFile = parsed[1];
        if (htmlFile == "/")
        {
            htmlFile = "/index.html";
        }
    }

    // Open the document in the local file system
    std::ifstream f("/Users/soyoon/ws/code/2021/server-from-scratch/wwwroot" + htmlFile);

    if (f.good())
    {
        std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        content = str;
        statusCode = 200;
    }
    f.close();

    // Write the document back to the client

    std::ostringstream oss;
    oss << "HTTP/1.1 " << statusCode << " OK\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "\r\n";
    oss << content;

    std::string output = oss.str();
    int size = output.size() + 1;

    Send(clientSocket, output.c_str(), size);
}