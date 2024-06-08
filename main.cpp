#include <joy.hpp>
#include <server.hpp>
#include <iostream>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Pass target network device as argument(vm|raspberry) and choose joy device e.g. /dev/input/js2!" << std::endl;
        return 0;
    }

    char ip_addr[16];
    if(strcmp(argv[1], "vm") == 0)
        strcpy(ip_addr, "192.168.0.159");
    else if(strcmp(argv[1], "raspberry") == 0)
        strcpy(ip_addr, "192.168.0.195");
    else
    {
        std::cout << "invalid network device argument!" << std::endl;
        return 0;
    }

    if (int ret = open_socket(ip_addr) != 0)
    {
        std::cout << "Error socket initialization with: " << ret << " return code" << std::endl;
    }

    if(initialize_joy(argv[2]) != 0)
    {
        std::cout << "Error joy initialization!" << std::endl;
        return -1;
    };

    std::string cmd = "empty_string";
    std::cout << "before loop" << std::endl;
    JS_DATA_TYPE data;
    while(true)
    {
        if (read_joy_state(data) != -1)
            send_command(data);
        usleep(50000);
    }

    close_connection();
    return 0;
}
