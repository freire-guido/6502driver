#include <EEPROM.h>
#include "busmanager.h"

const int addr_bus[8] = {4, 5, A0, A1, A2, A3, A4, A5};

void setup() {
  Serial.begin(9600);
  for (int addr : addr_bus) {
    pinMode(addr, INPUT);
  }
}

void loop() {
  for (int i = 0; i < 256; i++) {
    Serial.print(EEPROM[i]);
    Serial.print(" ");
    if (i % 16 == 15) {
      Serial.println("");
    }
  }
  Serial.println("");
  Serial.println("------------");
  Serial.println("");
}
