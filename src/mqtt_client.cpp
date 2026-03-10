#include "alarm.h"
#include "mqtt_client.h"
#include "wifi_manager.h"
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>
#define MQTT_SEND_TIME 2000 // skicka MQTT varannan sek
#define MQTT_RECONNECT_TIME 2000 // reconnect varannan sek

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[]              = "192.168.1.101";
int port                         = 1883;
const char indoorTempTopic[]     = "sensor/indoorTemp";
const char indoorHumidTopic[]    = "sensor/indoorHumidity";
const char waterleakTopic[]      = "sensor/waterleak";
const char fireTopic[]           = "sensor/fire";
const char systemFailure[]       = "systemFailure";

//bool tryMQTTconnect = false;
unsigned long MQTTConnectTimer = 0;
unsigned long MQTTLastSendTimer = 0;

bool manageMQTT() {
    // d) LWT: Maxtid, 10s offline -> ESP ger larm 
    // skriv testamentet här...
    
    if ((node.sysTime - MQTTConnectTimer >= MQTT_RECONNECT_TIME) && (!node.connectionStatus.mqttIsActive)){
        MQTTConnectTimer = node.sysTime;

        if (mqttClient.connect(broker, port)) {
            node.connectionStatus.mqttIsActive = true;
            initSendMQTT();
            return true;

        } else {
            node.connectionStatus.mqttIsActive = false;
            Serial.println("<< MQTT : Connect error >> Test in 2 sec");
            return false;
        }
    }

}

void initSendMQTT(){
        // one-time, init messages
    }

// -- avgör om datan behöver publiseras - Beroende på sensorer/status samt state --
void sendMQTT(){
    // .poll() : håller igång anslutningen (ping) - och skickar/tar emot MQTT
    mqttClient.poll();

    if (node.sysTime - MQTTLastSendTimer >= MQTT_SEND_TIME){
        MQTTLastSendTimer = node.sysTime;
        mqttClient.beginMessage(indoorTempTopic);
        mqttClient.print(node.sensors.indoorTemp);
        if (mqttClient.endMessage()) {
            Serial.println("Temp: Sent OK!");
        }

        mqttClient.beginMessage(indoorHumidTopic);
        mqttClient.print(node.sensors.indoorHumidity);
        if (mqttClient.endMessage()) {
            Serial.println("Humidity: Sent OK!");
        }

        if (node.alarmStatus.fireAlarm){
            mqttClient.beginMessage(fireTopic);
            mqttClient.print(node.sensors.fireTemp);
            mqttClient.print(node.sensors.smokeSensor);
            if (mqttClient.endMessage()) {
                Serial.println("Fire: Sent OK!");
        }
    }

        if (node.alarmStatus.waterLeak){
            mqttClient.beginMessage(waterleakTopic);
            mqttClient.print(node.sensors.waterLeak);
            if (mqttClient.endMessage()) {
                Serial.println("Water: Sent OK!");
            }
        }

        if (node.alarmStatus.systemFailure){
            // skicka releveant larm
        }
    }
        // c) skicka heartbeat var 30e sek (bra trots LWT)
}

void receiveMQTT(){


    // TA EMOT data (sub) från ESP -> "state"
}