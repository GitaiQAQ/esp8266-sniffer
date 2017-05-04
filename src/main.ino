#include <main.h>

const int led = 16;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  delay(100);
  digitalWrite(led, 1);

  Serial.println("");
  Serial.println("");
  Serial.println(" ___  _  _  ____  ____  ____  ____  ____ ");
  Serial.println("/ __)( \\( )(_  _)( ___)( ___)( ___)(  _ \\");
  Serial.println("\\__ \\ )  (  _)(_  )__)  )__)  )__)  )   /");
  Serial.println("(___/(_)\\_)(____)(__)  (__)  (____)(_)\\_)");
  Serial.println("");
  Serial.printf(" Version: %s:%d\n", SNIFFER_VERSION_NAME, SNIFFER_VERSION_CODE);
  Serial.println(" ©2017 Gitai.me");
  Serial.println("");
  Serial.println("");

  Serial.println("AIR CONFIG START\n");
  airconfig_start();
  Serial.print("AIR CONFIG END\n");
}

void loop() {
  delay(10);
  ota_loop();
  httpserver_loop();
}