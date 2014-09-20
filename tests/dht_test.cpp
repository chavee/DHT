
#include "DHT.h"
#include <application.h>

DHT dht(2, 22);

#define led 7

void setup(){
    Spark.disconnect();
    Serial.begin(115200);
    //Spark.variable("temperature", &(dht.temperature), INT);
    //Spark.variable("humidity", &(dht.humidity), INT);
    pinMode(led, OUTPUT);
    dht.init();
}

void blink(){
    static uint16_t start = millis();
    if((uint16_t)(millis() - start) < 1000){
        return;
    }
    start = millis();
    digitalWrite(led, 1 - digitalRead(led));
    Serial.println("blinking...");
}

void loop(){
    blink();
    if(dht.read() == true){
        Serial.print("Temperature C:\t"); Serial.println(dht.temperature);
        Serial.print("Humidity:\t"); Serial.println(dht.humidity);
    }
}

