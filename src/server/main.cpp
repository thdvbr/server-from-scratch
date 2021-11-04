#include "tcpListener.h"


void Listener_MessageReceived(TcpListener *listener, int client, std::string msg)
{
    listener->Send(client, msg);
}

int main()
{
    TcpListener server("127.0.0.1", 54000, Listener_MessageReceived);
    server.Run();
}
