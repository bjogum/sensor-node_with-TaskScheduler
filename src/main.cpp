#include <Arduino.h>
#include "scheduler.h"
#include "sensor_dht11.h"
#include "tasks.h"
#include "alarm.h"
#include <ArduinoBLE.h>

void setup() {
  Serial.begin(115200);
  while (!Serial); // testar om detta behövs..
  delay(2000); // testar om detta behövs..
  initComponents();
  // attachInterrupt --- HW interrupt: bryter pågående (lägre prioriterad) process omedelbart
}

void loop() { 
  node.sysTime = millis();
  startingSystem();
  
  if (node.runStatus == RUNNING){
    taskScheduler(); 
  }
}