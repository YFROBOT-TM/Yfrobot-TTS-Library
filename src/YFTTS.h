
#ifndef YFTTS_H
#define YFTTS_H

#include <Arduino.h>
#include "UTF8ToGB2312.h"

#include <SoftwareSerial.h>

class YFTTS {
public:
    YFTTS(int rxPin, int txPin);
    void begin(long baudRate);
    void speak(const char *data);
    void setTTSParameters(char parameter, int value);
    int checkWorkState();

private:
    U2GB u2gb;
    SoftwareSerial _serial;
    void sendData(const char *data);
    unsigned char calculateXOR(const unsigned char *data, int length);
};

#endif
