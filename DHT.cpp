int dht = D0;
int rh = 0;
int temp = 0;

DHT::DHT(uint8_t pin, uint8_t type){
    _pin = pin;
    _type = type;
}


void DHT::init(){
    digitalWrite(pin, HIGH);
    pinMode(_pin, INPUT_PULLUP);
}

#define MIN_PERIOD 1970
#define US_DELAY 5
#define WHILE_NOBLOCK(value) \
    for(_noblock=0; (value); _noblock++){ \
        delayMicroseconds(US_DELAY); \
        if(_noblock == 255) return -1; \
    }


int8_t DHT::read(){
    static uint8_t place;
    static uint16_t start;
    uint8_t _noblock;
    uint8_t data[5] = {0, 0, 0, 0, 0};

    switch(place){
    case 0:
        digitalWrite(_pin, LOW);
        pinMode(_pin, OUTPUT);

        start = millis();
        place = 1;
    case 1:
        if((uint16_t)(millis() - start) < 20){
            return false;
        }
        noInterrupts();
        digitalWrite(_pin, HIGH);
        pinMode(_pin, INPUT_PULLUP);

        WHILE_NOBLOCK(digitalRead(_pin) == HIGH);
        WHILE_NOBLOCK(digitalRead(_pin) == LOW);
        WHILE_NOBLOCK(digitalRead(_pin) == HIGH);
        for (uint8_t i = 0; i < 40; i++) {
            uint8_t counter = 0;
            WHILE_NOBLOCK(digitalRead(_pin) == LOW);
            for(_noblock=0; digitalRead(_pin) == HIGH; _noblock++){
                delayMicroseconds(US_DELAY);
                counter++;
                if(_noblock == 255) return -1;
            }

            data[i/8] <<= 1;
            if (counter > 4) {
                data[i/8] |= 1;
            }
        }
        interrupts();

        if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
            valid = false;
            goto end;
        }

        humidity = ((data[0] << 8) + data[1]);
        humidity /= 10;
        temperature = (((data[2] bitand 0x7F) << 8) + data[3]);
        temperature /= 10;
        if(data[2] bitand 0x80){
            temperature *= -1;
        }
        valid = true;
        start = millis();
        place = 2;
        return true;
end:
    case 2:
        place = 2;
        if((uint16_t)(millis() - start) < MIN_PERIOD){
            return false; // will return true only once
        }
        place = 0;
    }
}

