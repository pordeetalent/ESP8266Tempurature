#include <ESP8266WiFi.h>
#include "DataRead.h"
#include "Line_Data.h"
#include "MQTT_msg.h"

#define LED_BUILTIN D4

void setup() {
  Serial.begin(115200);
  Serial.println("/nstart");
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  setMqtt();
  Linesetup();
}

void loop() {
  mqtt_msg(Temp());
  while (volt() < 150) {
    if (volt() < 90) {
      mqtt_msg("Power off");
      Line_msg("Power off");
    }
    else {
      mqtt_msg("Voltage is low: " + String(volt()) + " V");
      Line_msg("Voltage is low: " + String(volt()) + " V");
    }
    mqtt_msg(Temp());
    Line_msg(Temp());
    for (int i = 1; i <= 60; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(800);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
  }

  for (int i = 1; i <= 60; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(800);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
