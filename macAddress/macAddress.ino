#include <WiFi.h>

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  //Nothing here
}
