// --- definierar NÄR resp. funktion ska köras ---
#include <stdio.h>
#include <Arduino.h>
#include "tasks.h"

// enum för resp. PRIO-klass.
enum TaskType {sensorPrio1, sensorPrio2, sensorPrio3, serviceBLE, serviceWiFi};

// struct för resp. TASK, innehållande: [Prioklass/funktion] - [intervall (ms)] - [senaste körningen (ms)]
// [ersätter ev. prioType med funktionspekare senare..]
struct Tasks {
    TaskType prioType;
    const unsigned long intervall;
    unsigned long lastRun;
};

// Tasks-array: "taskList" -> innehåller samtliga TASKS. ( utelämnar parametern lastRun->0) ) 
Tasks taskList[] = {
    {sensorPrio1, 20},    // Security sensors              -> 20ms?
    {sensorPrio2, 500},   // Saftey sensors                -> 500ms
    {sensorPrio3, 1500},  // Temp, fukt, lekage            -> 1500ms
    {serviceBLE, 100,50}, // håll BLE aktivt & skcka data - lastRun 50ms ("offset"): underviker krock med Wifi-> 100ms
    {serviceWiFi, 100},   // håll WiFi aktivt & skcka data -> 100ms
};

void taskScheduler(){
  const int numOfTasks = sizeof(taskList) / sizeof(taskList[0]);
  unsigned long sysTime = millis();

  // Loopa igenom listan med TASKS (taskList) & checka tiden.
  for (int i; i<numOfTasks; i++){
    if (sysTime - taskList[i].lastRun >= taskList[i].intervall){

      // kör den task det är dax att köra
      switch (taskList[i].prioType)
      {
      case sensorPrio1:
        // security
        // triggar någon sensor -> sätts extern var. till True
        break;
      case sensorPrio2:
        // saftey (fire)
        // triggar någon sensor -> sätts extern var. till True
        break;
      case sensorPrio3:
        readPrio3Sensors();
        printf("\n<-----PRIO3_READ----->\n");
        break;
      case serviceBLE:
        // håll Wifi & BLE igång -> skicka aktuell data
        break;
      case serviceWiFi:
        // ...?
        break;
      }
      taskList[i].lastRun = sysTime;
    }
  };
  
  // Kolla om den nuvarande TASKEN bör köras - alltså: är nuvarande tid MINUS lastrun mer eller lika med intervall?
  // Om TRUE -> kör
      // switch-case -> Prio3=readPrio3Sensors();
  // Om FALSE -> loopa vidare

   // läs (Prio 3) sensorer -> var 2:e sek? * 2.

  // 
  // om larm triggats - skicka till ESP (via BLE)


};

