#include <joy.hpp>
#include <server.hpp>
#include <iostream>
#include <unistd.h>

int main(int argc, int** argv)
{
    open_socket();
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
