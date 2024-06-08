#pragma once
#include <string>
#include <linux/joystick.h>



int initialize_joy(const char*);
void exitFunc(int);
int read_joy_state(JS_DATA_TYPE&);
