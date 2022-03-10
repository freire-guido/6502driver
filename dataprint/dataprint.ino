#include <EEPROM.h>
#include "busmanager.h"
#include "oscillator.h"

const int ph = 2;
const int osc = 3;
const int addr_bus[8] = {4, 5, A5, A4, A3, A2, A1, A0};
const int data_bus[8] = {6, 7, 8, 9, 10, 11, 12, 13};

bool serviced = false;

void setup() {
  Serial.begin(9600);
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, INPUT);
  }
  pinMode(ph, INPUT);
  oscillate(1000000, osc);
  Serial.println("RDY");
}

void loop() {
  if (!serviced && digitalRead(ph) == LOW) {
    int data = readBus(data_bus, 8);
    int address = readBus(addr_bus, 8);
    Serial.print("data: ");
    Serial.print(data, BIN);
    Serial.print(' ');
    Serial.println(data, HEX);
    Serial.print("addr: ");
    Serial.print(address, BIN);
    Serial.print(' ');
    Serial.println(address, HEX);
    Serial.println("--------"); 
    serviced != serviced;
  }
  if (digitalRead(ph) == HIGH) {
    serviced = false;
  }
}
