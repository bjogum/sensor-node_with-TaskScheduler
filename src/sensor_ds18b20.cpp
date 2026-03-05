#include <OneWire.h>
#include <Arduino.h>
#include <DallasTemperature.h>

// Definiera pin - (DI)
const int ONE_WIRE_BUS = 4;

// Skapa "one wire" instans
OneWire oneWire(ONE_WIRE_BUS);

// Skapa "sensorn"
DallasTemperature ds18b20(&oneWire);

void initDS18B20() {
    ds18b20.begin(); // startsekvensen
    Serial.println("DS18B20 Initierad");
}

