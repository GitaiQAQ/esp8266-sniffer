extern "C" {
  #include <user_interface.h>
  #include <gpio.h>
}

#include <airconfig.h>
#include <httpserver.h>
#include <OTA.h>

#define SNIFFER_DEBUG 0
#define SNIFFER_VERSION_CODE 1705041518
#define SNIFFER_VERSION_NAME "v0.2.3"

void setup();
void loop();