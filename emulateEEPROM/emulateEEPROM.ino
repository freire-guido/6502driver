#include <EEPROM.h>
#include "busmanager.h"
#include "oscillator.h"

const int addr_bus[16] = {1, 1, 1, 1, 1, 1, 1, 1, 4, 5, A5, A4, A3, A2, A1, A0};
const int offset = 0xFF00;
// data bus is actually 8 bits (pins 4 - 5 and A5 - A0) long, 1s are trash
const int data_bus[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const int CS = 0;
const int RS = 1;
bool serviced = false;

void setup() {
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, OUTPUT);
  }
  pinMode(1, INPUT_PULLUP); // 1s are trash
  pinMode(CS, INPUT);

  eepromClear();
  EEPROM[0xFFFC - offset] = 0x00;
  EEPROM[0xFFFD - offset] = 0xFF;

  Serial.begin(115200);
  Serial.println(EEPROM.length());
  hexdump();
  Serial.println("RDY");
}

void loop() {
  while (!serviced) {
    if (digitalRead(CS) == LOW) {
      int address = readBus(addr_bus, 16) - offset;
      writeBus(data_bus, EEPROM[address]);
      Serial.print(address, BIN);
      Serial.print(' ');
      Serial.println(address, HEX);

      serviced = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }  if (digitalRead(CS) == HIGH) {
    serviced = false;
    digitalWrite(LED_BUILTIN, LOW);
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
  if (digitalRead(RS) == LOW) {
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
    hexdump();
    eepromClear();
  }
}