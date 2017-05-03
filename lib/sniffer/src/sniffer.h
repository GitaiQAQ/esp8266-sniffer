#include "ArduinoOTA.h"

extern "C" {
  #include <user_interface.h>
  #include <gpio.h>
  #include <string.h>
}

#define DATA_LENGTH           		112

#define TYPE_MANAGEMENT       		0x00
#define TYPE_CONTROL          		0x01
#define TYPE_DATA             		0x02
#define SUBTYPE_PROBE_REQUEST 		0x04
#define CHANNEL_HOP_INTERVAL_MS   	1000
#define DISABLE 					0
#define ENABLE  					1

struct RxControl {
 signed rssi:8; // signal intensity of packet
 unsigned rate:4;
 unsigned is_group:1;
 unsigned:1;
 unsigned sig_mode:2; // 0:is 11n packet; 1:is not 11n packet;
 unsigned legacy_length:12; // if not 11n packet, shows length of packet.
 unsigned damatch0:1;
 unsigned damatch1:1;
 unsigned bssidmatch0:1;
 unsigned bssidmatch1:1;
 unsigned MCS:7; // if is 11n packet, shows the modulation and code used (range from 0 to 76)
 unsigned CWB:1; // if is 11n packet, shows if is HT40 packet or not
 unsigned HT_length:16;// if is 11n packet, shows length of packet.
 unsigned Smoothing:1;
 unsigned Not_Sounding:1;
 unsigned:1;
 unsigned Aggregation:1;
 unsigned STBC:2;
 unsigned FEC_CODING:1; // if is 11n packet, shows if is LDPC packet or not.
 unsigned SGI:1;
 unsigned rxend_state:8;
 unsigned ampdu_cnt:8;
 unsigned channel:4; //which channel this packet in.
 unsigned:12;
};

struct SnifferPacket{
    struct RxControl rx_ctrl;
    uint8_t data[DATA_LENGTH];
    uint16_t cnt;
    uint16_t len;
};

static void showMetadata(SnifferPacket*);

/**
 * Callback for promiscuous mode
 */
static void ICACHE_FLASH_ATTR sniffer_callback(uint8_t *, uint16_t);
static void printDataSpan(uint16_t, uint16_t, uint8_t*);
static void getMAC(char *, uint8_t*, uint16_t);

/**
 * Callback for channel hoping
 */
void channelHop();
void sniffer_setup();