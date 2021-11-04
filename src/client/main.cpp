#include "tcpClient.h"

int main()
{

    TcpClient client("127.0.0.1", 54000);
    client.Run();
}