#include <EEPROM.h>
#include "busmanager.h"
#include "oscillator.h"

const int OSC = 10;
const int PH2 = 11;
const int ADDR[16] = {2, 3, 4, 5, 6, 7, 8, 9, PH2, PH2, PH2, PH2, PH2, PH2, PH2, PH2};
const int DATA[8] = {A5, A4, A3, A2, A1, A0, 12, 13};

const int offset = 0xFF00;

void setup() {
  pinMode(PH2, INPUT);
  oscillate(1000000, OSC);
  Serial.begin(9600);
  Serial.println("RDY");
}

void loop() {
  unsigned int address = readBus(ADDR, 16);
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
  while (digitalRead(PH2) == LOW) {
    Serial.println();
  };
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

void serialEvent() { 
  eepromClear();
  EEPROM[0xFFFC - offset] = 0x00;
  EEPROM[0xFFFD - offset] = 0xFF;
  String message = Serial.readString();
  Serial.println(message.length());
  byte buffer[16];
  int b = 0;
  int j = message.indexOf('\n');
  for (int i = 0; i < message.length() && j != -1; i = j + 1) {
    strToBytes(message.substring(i, j), buffer, 16);
    for (int a = 0; a < 16; a++) {
      EEPROM[b + a] = buffer[a];
    }
    b += 16;
    j = message.indexOf('\n', j + 1);
  }
  hexdump();
}
