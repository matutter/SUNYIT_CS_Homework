//General includes:
#include <iostream>         // 
#include <stdio.h>          // 
#include <string>           // 
#include <sys/socket.h>     // 
#include <netdb.h>          // 
#include <arpa/inet.h>      // 
#include <cstdlib>
#include <strings.h>

#define PORT 8888
#define HOST "168.192.0.0"

using namespace std;

void client_tick(string);

int main(int argc, char *argv[])
{
    string message = "{ \"hello\": \"world\" }";

    client_tick(message);

    return 0;
}

void client_tick(string message)
{
    int sd, ret;
    struct sockaddr_in server;
    struct in_addr     addr;
    // char*    h_name
    // int      h_length
    // char**   h_aliases
    // int      h_addrtype
    struct hostent     *host;

    sd = socket(AF_INET,SOCK_DGRAM,0); //find open socket
    cout << sd << endl;

    server.sin_family = AF_INET;

    inet_pton(AF_INET, HOST, &addr);
    host = gethostbyaddr(&addr, sizeof addr, AF_INET);
    host = gethostbyname(HOST);

    cout << host->h_name << ":" << PORT << endl;


    bcopy(host->h_addr, &(server.sin_addr.s_addr), host->h_length);
    server.sin_port = htons(PORT);

    connect(sd, (const sockaddr *)&server, sizeof(server));
    send(sd, (char *)message.c_str(), message.length(), 0);
}