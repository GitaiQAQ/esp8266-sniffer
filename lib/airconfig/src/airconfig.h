extern "C" {
  #include <user_interface.h>
  #include <gpio.h>
  #include <string.h>
  #include <upgrade.h>
  #include <smartconfig.h>
  #include <airkiss.h>
}

#include "ArduinoOTA.h"
#include <httpserver.h>
#include <sniffer.h>

void  ICACHE_FLASH_ATTR airconfig_done(sc_status , void  *);
void airconfig_start();
void airconfig_stop(int fail);