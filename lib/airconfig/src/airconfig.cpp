#include <airconfig.h>

const int led = 16;
bool airconfig_run = false;

void smartconfig_done(sc_status  status, void  *pdata) {
  digitalWrite(led, 0);
  switch(status)  {
    case SC_STATUS_WAIT:{
      Serial.print("SC_STATUS_WAIT\n");
      break;
    } case SC_STATUS_FIND_CHANNEL:{
      Serial.print("SC_STATUS_FIND_CHANNEL\n");
      break;
    } case SC_STATUS_GETTING_SSID_PSWD:{
      Serial.print("SC_STATUS_GETTING_SSID_PSWD\n");
      sc_type *type = (sc_type *)pdata;
      if  (*type  ==  SC_TYPE_ESPTOUCH) {
        Serial.print("SC_TYPE:SC_TYPE_ESPTOUCH\n");
      } else  {
        Serial.print("SC_TYPE:SC_TYPE_AIRKISS\n");
      }
      break;
    } case SC_STATUS_LINK:{
      Serial.print("SC_STATUS_LINK\n");
      station_config *sta_conf = (station_config *)pdata;
      wifi_station_set_config(sta_conf);
      wifi_station_disconnect();
      wifi_station_connect();
      break;
    } case SC_STATUS_LINK_OVER:{
      Serial.print("SC_STATUS_LINK_OVER\n");
      if  (pdata  !=  NULL) {
        uint8 phone_ip[4] = {0};
        memcpy(phone_ip,  (uint8*)pdata,  4);
        Serial.print("Phone  ip:");
        Serial.print(phone_ip[0]);
        Serial.print(".");
        Serial.print(phone_ip[1]);
        Serial.print(".");
        Serial.print(phone_ip[2]);
        Serial.print(".");
        Serial.print(phone_ip[3]);
        Serial.println();
      }
      airconfig_stop(0);
      break;
    }
  }
}


void airconfig_stop(int fail){
  system_soft_wdt_feed();
  airconfig_run = true;
  smartconfig_stop();
  if (!fail) {
    Serial.print("HTTPServer START\n");
    httpserver_setup();
    Serial.print("HTTPServer END\n");

    Serial.print("OTA START\n");
    ota_setup();
    Serial.print("OTA END\n");

    Serial.print("AutoUpdate START\n");
    autoupdate_setup();
    Serial.print("AutoUpdate END\n");
  } else {
    Serial.print("Sniffer START\n");
    sniffer_setup();
    Serial.print("Sniffer END\n");
  }
}

void airconfig_start(){
  pinMode(led, OUTPUT);
	smartconfig_start(smartconfig_done);
  for(uint8_t t = 45; !airconfig_run && t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      delay(1000);
  }
  if (wifi_station_get_connect_status()!=STATION_GOT_IP) airconfig_stop(1);
}