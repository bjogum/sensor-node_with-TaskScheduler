#include <Arduino.h>
#include "scheduler.h"
#include "sensor_dht11.h"
#include "wifi_manager.h"


void setup() {
  Serial.begin(115200);
  delay(2000); // För DHT11, behöver uppstartstid innan init
  initWiFi();
  initDHT(); 
  // attachInterrupt --- HW interrupt: bryter pågående (lägre prioriterad) process omedelbart
}

void loop() {
  taskScheduler(); 
}