#include <main.h>

const int led = 16;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  delay(100);
  digitalWrite(led, 1);

  Serial.printf("Sniffer %s:%d\n", VERSION_NAME, VERSION_CODE);

  Serial.print("AIR CONFIG START\n");
  airconfig_start();
  Serial.print("AIR CONFIG END\n");
}

void loop() {
  delay(10);
  ota_loop();
  httpserver_loop();
}
