#include <ESP8266WiFi.h>
#include "random.h"
#include "global.h"
#include "aws.h"
#include "DataRead.h"
#include "Line_Data.h"

#define LED_BUILTIN D4
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.setDebugOutput(0); 
  generateClientID();
  init_AWS_service();
  
  Serial.println("/nstart");
  dht.begin();

  Linesetup();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) 
  {
     set_wifi();
     AWS_Setup();
  }
  if(Finish==1)
  {
     Serial.printf("AWS_data %s\n",AWS_data);
     AWS_pub();
     Finish=0;
  }

  AWS_msg(Temp());
  while (volt() < 150) {
    if (volt() < 90) {
      AWS_msg("Power off");
      Line_msg("Power off");
    }
    else {
      AWS_msg("Voltage is low: " + String(volt()));
      Line_msg("Voltage is low: " + String(volt()));
    }
    AWS_msg(Temp());
    Line_msg(Temp());
    for (int i = 1; i <= 10; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(800);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
  }
  
  AWS_callback();
  
  for (int i = 1; i <= 10; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(800);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
