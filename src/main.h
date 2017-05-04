extern "C" {
  #include <user_interface.h>
  #include <gpio.h>
}

#include <airconfig.h>
#include <httpserver.h>
#include <autoupdate.h>
#include <OTA.h>

#define SNIFFER_DEBUG 0
#define SNIFFER_VERSION_CODE 1705042022
#define SNIFFER_VERSION_NAME "v0.2.5"

#define USE_SERIAL Serial

void setup();
void loop();