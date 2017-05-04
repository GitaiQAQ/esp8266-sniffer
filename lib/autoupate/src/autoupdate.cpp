#include <update.h>

void update_setup(){
    t_httpUpdate_return ret = ESPhttpUpdate.update("192.168.10.139", 8080, "");
    switch(ret) {
        case HTTP_UPDATE_FAILED:
            Serial.printf("[update] Update failed. (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("[update] Update no Update.");
            break;
        case HTTP_UPDATE_OK:
            Serial.println("[update] Update ok."); // may not called we reboot the ESP
            break;
    }
}