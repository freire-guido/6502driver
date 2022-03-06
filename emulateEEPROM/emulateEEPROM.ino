#include <EEPROM.h>
#include "busmanager.h"

const int addr_bus[8] = {4, 5, A0, A1, A2, A3, A4, A5};
const int data_bus[8] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, OUTPUT);
  }
  eepromClear();
  Serial.begin(9600);
}

void loop() {
  
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

void strToBytes(String str, byte buff[], int _sz, char delim = ' ') {
  int b = 0;
  int j = 0;
  for (int i = 0; b < _sz && j != -1; i = j + 1) {
    j = str.indexOf(delim, i + 1);
    buff[b] = byte(str.substring(i, j).toInt());
    b++;
  }
}

void serialEvent() {
  digitalWrite(LED_BUILTIN, HIGH);
  String message = Serial.readString();
  Serial.println(message.length());
  byte buffer[16];
  int b = 0;
  int j = 0;
  for (int i = 0; j < message.length() && j != -1; i = j + 1) {
    j = message.indexOf('\n', i + 1);
    strToBytes(message.substring(i, j), buffer, sizeof(buffer));
    for (int a = 0; a < sizeof(buffer); a++) {
      EEPROM[b + a] = buffer[a];
    }
    b += sizeof(buffer);
  }
  digitalWrite(LED_BUILTIN, LOW);
  hexdump();
  eepromClear();
}