#include <EEPROM.h>
#include "busmanager.h"
#include "oscillator.h"

const int osc = 3;
const int addr_bus[8] = {4, 5, A0, A1, A2, A3, A4, A5};
const int data_bus[8] = {6, 7, 8, 9, 10, 11, 12, 6};

void setup() {
  Serial.begin(9600);
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
  for (int data : data_bus) {
    pinMode(data, INPUT);
  }
  oscillate(1000000, osc);
  Serial.println("RDY");
}

void loop() {
  Serial.print("data: ");
  Serial.println(readBus(data_bus, 8), BIN);
  Serial.print("addr: ");
  Serial.println(readBus(addr_bus, 8), BIN);
  Serial.println("--------");
  delay(500);
}
