#include <joy.hpp>
#include <server.hpp>
#include <iostream>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Pass target network device as argument(vm|raspberry)!" << std::endl;
        return 0;
    }

    char ip_addr[16];
    if(strcmp(argv[1], "vm"))
        strcpy(ip_addr, "192.168.0.159");
    else if(strcmp(argv[1], "raspberry"))
        strcpy(ip_addr, "192.168.0.195");
    else
    {
        std::cout << "invalid argument!" << std::endl;
        return 0;
    }

    if (int ret = open_socket(ip_addr) != 0)
    {
        std::cout << "Error socket initialization with: " << ret << " return code" << std::endl;
    }
    if(initialize_joy() != 0)
    {
        std::cout << "Error joy initialization!" << std::endl;
        return -1;
    };

    std::string cmd = "empty_string";
    std::cout << "before loop" << std::endl;
    while(true)
    {
        read_joy_state(cmd);
        send_command(cmd);
        usleep(50000);
    }

    close_connection();
    return 0;
}
