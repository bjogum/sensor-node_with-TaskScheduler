## Alarm sensor node, with custom task scheduler → ![](https://img.shields.io/badge/status-under%20development-8A2BE2)
#### Overview
This is a modular component of a larger IoT system (Smart Hub) consisting of multiple nodes.

This repo handles all sensor data for an alarm system, utilizing an Arduino Uno R4 WiFi with a bespoke non-blocking task scheduler to manage concurrent sensor polling and network communication. Sensor data is distributed to neighboring nodes via Wi-Fi using the MQTT protocol, and via BLE.


...more info is coming

#### Architecture
...

#### Features
...

#### Hardware
* MCU: Arduino Uno R4 WiFi

* Sensors:

| Sensors       | Detect                  | PIN | Transmits to  | 
| ------------- |:-----------------------:|:---:| -------------:|
| DHT11         | Indoor: temp + humidity | D2  | Broker @ MQTT |
| DS18B20       | Temp, fire              | D5  | Broker @ MQTT |
| MQ2           | Gas, fire               |  -  | Broker @ MQTT |
| Rain-sensor   | Water leak              |  -  | Broker @ MQTT | 
| PIR           | Motion                  |  -  | ESP32 @ BLE   |
| Reed          | Open door / window      |  -  | ESP32 @ BLE   |


