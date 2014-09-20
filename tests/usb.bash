rm firmware*; spark compile \
../DHT.cpp \
../DHT.h \
dht_test.cpp \
; spark flash --usb firmware*
