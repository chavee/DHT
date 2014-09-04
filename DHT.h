#ifndef __dht_h
#define __dht_h

#ifdef SPARK
#include <application.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>

class DHT{
public:
    DHT(uint8_t pin, uint8_t type);
    void init();
    float temperature = 0;
    float humidity = 0;
    bool valid;
    int8_t read();
private:
    uint8_t _pin;
    uint8_t _type;
    uint8_t place = 0;
    uint16_t start;
};
#endif
