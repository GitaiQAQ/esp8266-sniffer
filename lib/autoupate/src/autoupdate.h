extern "C" {
  #include <user_interface.h>
}

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#define VERSION_CODE 0
#define VERSION_NAME "v0.0.1"

#ifdef SNIFFER_VERSION_CODE
  #define VERSION_CODE SNIFFER_VERSION_CODE
#endif
#ifdef SNIFFER_VERSION_NAME
  #define VERSION_NAME SNIFFER_VERSION_NAME
#endif

#define USE_SERIAL Serial

void autoupdate_setup();
void autoupdate_loop();