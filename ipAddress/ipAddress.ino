#include <WiFi.h>

const char* ssid ="xxxxx";      // Replace with your Wi-Fi network name (SSID)
const char* password = "xxxxx"; // Replace with your Wi-Fi network password

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  // Check if connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {
    // Get and print the local IP address
    Serial.print("The IP address is: ");
    Serial.println(WiFi.localIP());
  }
  
  delay(5000); // Wait for 5 seconds
}
