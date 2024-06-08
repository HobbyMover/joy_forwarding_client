#pragma once

int open_socket(const char*);
void close_connection();
int send_command(std::string&);
