#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sstream>
#include "joy.hpp"


int joy_fd = -1;

void exitFunc(int fd)
{
  close(fd);
  if (ioctl(fd, UI_DEV_DESTROY) < 0)
  {
    printf("Error destroying gamepad! \n");
  }
}

int initialize_joy(const char* device)
{
    int rcode = 0;

    char joy_name[256] = "Unknown";
    joy_fd = open(device, O_RDONLY | O_NONBLOCK); // open in non-blocking mode
    if (joy_fd == -1)
    {
      printf("Failed to open joystick.\n");
      return -1;
    }
    rcode = ioctl(joy_fd, EVIOCGNAME(sizeof(joy_name)), joy_name);
    printf("\nrcode: %i \n", rcode);
    printf("joy_fd: %i \n", joy_fd);
    printf("Reading From : %s \n", joy_name);
    return 0;
}

int read_joy_state(JS_DATA_TYPE& js_event)
{
   // joy_state.clear();
    //struct js_event joy_event;
    //static struct JS_DATA_TYPE js_event;
    //int ret = read(joy_fd, &joy_event, sizeof(joy_event));
    //if (read(joy_fd, &joy_event, sizeof(joy_event)) != -1)
    //{
    //    printf("joy event: type %d code %d value %d ret %i  \n", joy_event.type, joy_event.number, joy_event.value, ret);
    //}
    //joy_event = {};
    int ret = read(joy_fd, &js_event, sizeof(js_event));
    if (ret != -1)
    {
        printf("js event: buttons %d x %d y %d ret %i \n", js_event.buttons, js_event.x, js_event.y, ret);
        //std::ostringstream stream;
        //stream << js_event.buttons << " " << js_event.x << " " << js_event.y;
        //joy_state = stream.str();
    }
    return ret;
}
