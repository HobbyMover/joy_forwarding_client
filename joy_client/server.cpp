/*!
 * Simple chat program (client side).cpp - http://github.com/hassanyf
 * Version - 2.0.1
 *
 * Copyright (c) 2016 Hassan M. Yousuf
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

int client;

int open_socket(const char* ip)
{
    int portNum = 60123; // NOTE that the port number is same for both client and server

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket client has been created..." << endl;
    cout << "sssbefore inet!" << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    cout << "before inet!" << std::endl;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    cout << "after inet!" << std::endl;

    cout << "try to connect to server first time!" << std::endl;
    int ret = connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr));
    int counter = 0;
    while (ret != 0)
    {
        usleep(1000000);
        cout << "try to connect to server!" << std::endl;
        if (counter >= 100)
        {
            cout << "timeout connecting to server!" << std::endl;
            return -1;
        }
        ret = connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr));
    }
    return 0;
}

void close_connection()
{
    close(client);
}

void send_command(std::string& cmd)
{
    send(client, cmd.c_str(), cmd.size(), 0);
}
