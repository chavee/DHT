#ifndef __dht_h
#define __dht_h

#include <inttypes.h>

class DHT{
    private:
    uint8_t _pin;
    uint8_t _type;
    uint8_t place = 0;

    public:
    DHT(uint8_t pin, uint8_t type);
    float temperature = 0;
    float humidity = 0;
    bool valid;
    int8_t read();
}

#endif
