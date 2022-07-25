#include <EEPROM.h>
#include "busmanager.h"
#include "oscillator.h"

const int OSC = 10;
const int PH2 = 11;
const int ADDR[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int DATA[8] = {A5, A4, A3, A2, A1, A0, 12, 13};

const int offset = 0xFF00;

void setup() {
  pinMode(PH2, INPUT);

  eepromClear();
  EEPROM[0xFFFC - offset] = 0x00;
  EEPROM[0xFFFD - offset] = 0xFF;

  oscillate(0.1, OSC);

  Serial.begin(9600);
  Serial.println("RDY");
}

void loop() {
  unsigned int address = readBus(ADDR, 8);
  unsigned int data = readBus(DATA, 8);
  writeBus(DATA, EEPROM[address - offset]);
  Serial.print("DATA: ");
  Serial.print(data, BIN);
  Serial.print(' ');
  Serial.println(data, HEX);
  Serial.print("ADDR: ");
  Serial.print(address, BIN);
  Serial.print(' ');
  Serial.println(address, HEX);
  Serial.println("---");
  while (digitalRead(PH2) == LOW) {};
}

void eepromClear() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM[i] = 0;
  }
}

void hexdump() {
  for (int i = 0; i < EEPROM.length(); i++) {
    if (i % 16 == 0) {
      Serial.print('\n');
      Serial.print(i, HEX);
      Serial.print(' ');
    }
    Serial.print(EEPROM[i], HEX);
    Serial.print(' ');
  }
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
  eepromClear();
  String message = Serial.readString();
  Serial.println(message.length());
  byte buffer[16];
  int b = 0;
  int j = 0;
  for (int i = 0; j < message.length() && j != -1; i = j + 1) {
    j = message.indexOf('\n', i + 1);
    strToBytes(message.substring(i, j), buffer, 16);
    for (int a = 0; a < 16; a++) {
      EEPROM[b + a] = buffer[a];
    }
    b += 16;
  }
  hexdump();
}
