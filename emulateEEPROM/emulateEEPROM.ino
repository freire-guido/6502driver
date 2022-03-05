#include <EEPROM.h>
#include "busmanager.h"

const int addr_bus[8] = {4, 5, A0, A1, A2, A3, A4, A5};
const int data_bus[8] = {6, 7, 8, 9, 10, 11, 12, 13};
int Ei = 0;

void setup() {
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, OUTPUT);
  }
  eepromClear();
  Serial.begin(9600);
//  hexdump();
}

void loop() {
  
}

void serialEvent() {
  digitalWrite(LED_BUILTIN, HIGH);
  String buf;
  buf = Serial.readString();
  for (int i = 0; i < buf.length(); i++) {
    Serial.write(buf[i]);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void eepromClear() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM[i] = 0;
  }
}

void hexdump() {
  for (int i = 0; i < 256; i++) {
    Serial.print(EEPROM[i], HEX);
    Serial.print(' ');
    if (i % 16 == 15) {
      Serial.print('\n');
    }
  }
  Serial.print('\n');
}

byte strToBytes(String str, byte bytes[], int _sz = -1) {
  for (int i = 0; i < _sz || (_sz == -1 && str[i] == '\n'); i) {
    
  }
}