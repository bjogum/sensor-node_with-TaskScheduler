#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <stdio.h>

enum SensorState {
    READING_DHT,
    READING_WATER
};

void readPrio3Sensors();



#endif