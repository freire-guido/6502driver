#include <EEPROM.h>
#include "busmanager.h"

const int addr_bus[16] = {4, 4, 4, 4, 4, 4, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13};
// data bus is actually 10 bits (pins 3 and 5 - 13) long, 4s are trash
const int data_bus[8] = {1, 2, A0, A1, A2, A3, A4, A5};
const int CS = 0;
bool serviced = false;

void setup() {
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, OUTPUT);
  }
  pinMode(4, INPUT_PULLUP); // 4s are trash
  pinMode(CS, INPUT);

  eepromClear();
  EEPROM[0xFFFC] = 0x00;
  EEPROM[0xFFFD] = 0xFC;

  Serial.begin(9600);
  Serial.println("RDY");
}

void loop() {
  while (!serviced) {
    if (digitalRead(CS) == HIGH) {
      writeBus(data_bus, EEPROM[readBus(addr_bus, 16)]);
      serviced = true;
    }
  }
  if (digitalRead(CS) == LOW) {
    serviced = false;
  }
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