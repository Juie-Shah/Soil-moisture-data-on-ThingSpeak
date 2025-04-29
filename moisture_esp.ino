#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = " "; //enter network id
const char* password = " "; //enter password

WiFiClient client;

// ThingSpeak settings
unsigned long channelID = 2909359;
const char* writeAPIKey = "A9VJLZEYNA5CNA48";

// Sensor pin
const int moisturePin = 34;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  int rawValue = analogRead(moisturePin);
  float moisturePercent = 100 - ((rawValue / 4095.0) * 100); // ESP32 uses 12-bit ADC

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  ThingSpeak.setField(1, moisturePercent);
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("Data sent to ThingSpeak!");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(response);
  }

  delay(15000); // ThingSpeak allows updates every 15 seconds
}

