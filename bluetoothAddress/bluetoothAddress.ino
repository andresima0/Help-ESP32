#include "esp_bt_main.h"
#include "esp_bt_device.h"
 
void initBluetooth() {
  if (!btStart() || esp_bluedroid_init() != ESP_OK || esp_bluedroid_enable() != ESP_OK) {
    Serial.println("Failed to initialize Bluetooth");
  }
}
 
void printDeviceAddress() {
  const uint8_t* address = esp_bt_dev_get_address();
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X%s", address[i], (i < 5) ? ":" : "");
  }
}
 
void setup() {
  Serial.begin(115200);
  initBluetooth();
  Serial.print("ESP32 Bluetooth Address: ");
  printDeviceAddress();
}
 
void loop() {
  //Nothing here    
}