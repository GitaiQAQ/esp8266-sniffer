extern "C" {
  #include <user_interface.h>
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

void handleRoot();

void handleNotFound();
void httpserver_setup(void);
void httpserver_loop(void);