#include "DHT.h"

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

DHT::DHT(uint8_t pin, uint8_t type){
    _pin = pin;
    _type = type;
}

void DHT::init(){
    pinMode(_pin, INPUT_PULLUP);
    digitalWrite(_pin, HIGH);
    place=0;
}

#define MIN_PERIOD 1970
#define US_DELAY 5
#define WHILE_NOBLOCK(value) \
    for(_noblock=0; (value); _noblock++){ \
        delayMicroseconds(US_DELAY); \
        if(_noblock == 255) { \
            Serial.println("Error Block"); \
            goto error; \
        } \
    }

#define PPl() Serial.print("Pl:"), Serial.println(place)

int8_t DHT::read(){
    int8_t out = 0;
    uint8_t _noblock;
    uint8_t data[5] = {0, 0, 0, 0, 0};

    switch(place){
    case 0:
        PPl();
        start = millis();
        Serial.println("starting DHT");
    place = 1;
    case 1:
        if((uint16_t)(millis() - start) < MIN_PERIOD){
            return false; // will return true only once
        }

        digitalWrite(_pin, LOW);
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, LOW);

        start = millis();
    place = 2;
    case 2:
        PPl();
        if((uint16_t)(millis() - start) < 20){
            return false;
        }
        Serial.println("taking data");

        noInterrupts();
        pinMode(_pin, INPUT_PULLUP);
        digitalWrite(_pin, HIGH);

        WHILE_NOBLOCK(digitalRead(_pin) == HIGH);
        WHILE_NOBLOCK(digitalRead(_pin) == LOW);
        WHILE_NOBLOCK(digitalRead(_pin) == HIGH);
        for (uint8_t i = 0; i < 40; i++) {
            uint8_t counter = 0;
            WHILE_NOBLOCK(digitalRead(_pin) == LOW);
            for(_noblock=0; digitalRead(_pin) == HIGH; _noblock++){
                delayMicroseconds(US_DELAY);
                counter++;
                if(_noblock == 255) {
                    goto error;
                    Serial.println("error counter");
                }
            }

            data[i/8] <<= 1;
            if (counter > 4) {
                data[i/8] |= 1;
            }
        }
        interrupts();

        if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
            Serial.println("Error End");
            goto error;
        }

        switch(_type){
            case DHT11:
                humidity = data[0];
                temperature = data[2];
                break;
            case DHT21:
            case DHT22:
                humidity = ((data[0] << 8) + data[1]);
                humidity /= 10;
                temperature = (((data[2] bitand 0x7F) << 8) + data[3]);
                temperature /= 10;
                if(data[2] bitand 0x80){
                    temperature *= -1;
                }
                break;
            default:
                Serial.println("Error Type");
                goto error;
        }
        valid = true;
        place = 0;
        return true;
error:
        interrupts();
        Serial.print("B:"); Serial.println(_noblock);

        valid = false;
        place = 0;
        return -1;
    }
}

