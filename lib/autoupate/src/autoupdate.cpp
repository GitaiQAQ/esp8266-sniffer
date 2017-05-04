#include <autoupdate.h>


void autoupdate_setup(){
    system_soft_wdt_feed();
}

ESP8266WiFiMulti WiFiMulti;
bool is_check=false;

void autoupdate_loop(){
  if(!is_check && (WiFiMulti.run() == WL_CONNECTED)){
    t_httpUpdate_return ret = ESPhttpUpdate.update("http://192.168.10.139:8080/firmware.bin");
    switch(ret) {
      case HTTP_UPDATE_FAILED:
        USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;
      case HTTP_UPDATE_NO_UPDATES:
        USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
        break;
      case HTTP_UPDATE_OK:
        USE_SERIAL.println("HTTP_UPDATE_OK");
        break;
    }
    is_check = !is_check;
  }
}