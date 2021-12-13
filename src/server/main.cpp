#include "webServer.h"
#include "tcpListener.h"

int main()
{
    // TcpListener server("127.0.0.1", 54000);
    WebServer server("0.0.0.0", 8080);
    server.Run();
}
