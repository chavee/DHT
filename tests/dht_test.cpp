
#include "DHT.h"
#include <application.h>

DHT dht(2, 22);

void setup(){
    Serial.begin(115200);
    Spark.variable("temperature", &(dht.temperature), INT);
    Spark.variable("humidity", &(dht.humidity), INT);
    dht.init();
}

void loop(){
    if(dht.read() == true){
        Serial.print("Temperature C:\t"); Serial.println(dht.temperature);
        Serial.print("Humidity:\t"); Serial.println(dht.humidity);
    }
}

