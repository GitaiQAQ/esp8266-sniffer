extern "C" {
  #include <user_interface.h>
  #include <gpio.h>
}

#include <airconfig.h>
#include <httpserver.h>

#define SNIFFER_DEBUG 0
#define VERSION_CODE 1705031133
#define VERSION_NAME "v0.2.1"

void setup();
void loop();