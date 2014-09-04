
#include "DHT.h"

DHT dht(2, 22);

void setup(){
    Serial.begin(115200);
    dht.init();
}

void loop(){
    if(dht.read() = true){
        Serial.print("Temperature C:\t"); Serial.println(dht.temperature);
        Serial.print("Humidity:\t"); Serial.println(dht.humidity);
    }
}

