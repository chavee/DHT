# DHT Digital Temperature / Humidity Sensor

This library is implementation of the DHT sensor. I got the origins of the code from
[some example code given on the spark forums](http://community.spark.io/t/simple-working-code-for-dht-sensors/3100)
. Because of it’s simplicity, it has proven to work better than the Adafruit library for me.

## How to use

Check out the tests folder for details, but essentially you have to call `init()` in the
setup function and call `read()` in your loop. The library will automatically handle the
correct delays, and will return `true` when it has gotten valid data.

Alternatively, when you have received valid data you can set `DHT.valid = false`
and continue to call `read()`. When `DHT.valid == true` the data will be ready to read.

Note: returns -1 on error. So *****do not** use `if(DHT.read())`
