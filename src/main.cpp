#include <Arduino.h>
#include "scheduler.h"
#include "sensor_dht11.h"
#include "wifi_manager.h"
#include "tasks.h"
#include <ArduinoBLE.h>

void setup() {
  Serial.begin(115200);
  initWiFi();
  sensorsInit();
  // attachInterrupt --- HW interrupt: bryter pågående (lägre prioriterad) process omedelbart
}

void loop() {
  taskScheduler(); 
}