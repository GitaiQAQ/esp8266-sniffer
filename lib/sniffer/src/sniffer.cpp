#include <sniffer.h>

static uint32_t chip_id;
uint32_t sequence = 0;
const int led = 16;

static void showMetadata(SnifferPacket *snifferPacket) {

  unsigned int frameControl = ((unsigned int)snifferPacket->data[1] << 8) + snifferPacket->data[0];

  uint8_t version      = (frameControl & 0b0000000000000011) >> 0;
  uint8_t frameType    = (frameControl & 0b0000000000001100) >> 2;
  uint8_t frameSubType = (frameControl & 0b0000000011110000) >> 4;
  uint8_t toDS         = (frameControl & 0b0000000100000000) >> 8;
  uint8_t fromDS       = (frameControl & 0b0000001000000000) >> 9;

  // Only look for probe request packets
  //if (frameType != TYPE_MANAGEMENT ||
  //    frameSubType != SUBTYPE_PROBE_REQUEST)
  //      return;

  digitalWrite(led, 0);

  char addr[] = "00:00:00:00:00:00";
  getMAC(addr, snifferPacket->data, 10);
  if (!strcmp(addr, "00:00:00:00:00:00") || !strcmp(addr, "ff:ff:ff:ff:ff:ff")){
    digitalWrite(led, 1);
    return;
  }
  
  Serial.print(version); // version: 

  Serial.print('|');
  Serial.print(frameType); // frameType: 

  Serial.print('|');
  Serial.print(frameSubType); // frameSubType: 

  Serial.print('|');
  Serial.print(chip_id); // UUID

  Serial.print('|');
  Serial.print(sequence++); // Sequence

  Serial.print('|'); // RSSI:
  Serial.print(snifferPacket->rx_ctrl.rssi, DEC);

  Serial.print('|'); // Channel
  Serial.print(wifi_get_channel());

  Serial.print('|'); // Sender MAC
  Serial.print(addr);

  getMAC(addr, snifferPacket->data, 4);
  Serial.print('|'); // Receiver MAC
  Serial.print(addr);

  Serial.print('|'); // SSID
  if (frameSubType == SUBTYPE_PROBE_REQUEST){
      uint8_t SSID_length = snifferPacket->data[25];
      printDataSpan(26, SSID_length, snifferPacket->data);
  }
  Serial.println();

  digitalWrite(led, 1);
}

/**
 * Callback for promiscuous mode
 */
static void ICACHE_FLASH_ATTR sniffer_callback(uint8_t *buffer, uint16_t length) {
  struct SnifferPacket *snifferPacket = (struct SnifferPacket*) buffer;
  showMetadata(snifferPacket);
}

static void printDataSpan(uint16_t start, uint16_t size, uint8_t* data) {
  for(uint16_t i = start; i < DATA_LENGTH && i < start+size; i++) {
    Serial.write(data[i]);
  }
}

static void getMAC(char *addr, uint8_t* data, uint16_t offset) {
  sprintf(addr, "%02x:%02x:%02x:%02x:%02x:%02x", data[offset+0], data[offset+1], data[offset+2], data[offset+3], data[offset+4], data[offset+5]);
}

/**
 * Callback for channel hoping
 */
void channelHop()
{
  // hoping channels 1-14
  uint8 new_channel = wifi_get_channel() + 1;
  if (new_channel > 14)
    new_channel = 1;
  wifi_set_channel(new_channel);
}

static os_timer_t channelHop_timer;

void sniffer_setup(){
  system_soft_wdt_feed();
  // set chip id as uuid
  chip_id = system_get_chip_id();
  
  pinMode(led, OUTPUT);
  // set the WiFi chip to "promiscuous" mode aka monitor mode
  wifi_set_opmode(STATION_MODE);
  wifi_set_channel(1);
  wifi_promiscuous_enable(DISABLE);
  delay(10);
  wifi_set_promiscuous_rx_cb(sniffer_callback);

  delay(10);
  wifi_promiscuous_enable(ENABLE);

  // setup the channel hoping callback timer
  os_timer_disarm(&channelHop_timer);
  os_timer_setfn(&channelHop_timer, (os_timer_func_t *) channelHop, NULL);
  os_timer_arm(&channelHop_timer, CHANNEL_HOP_INTERVAL_MS, 1);
}