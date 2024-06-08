#pragma once
#include <linux/joystick.h>

int open_socket(const char*);
void close_connection();
void send_command(JS_DATA_TYPE&);
