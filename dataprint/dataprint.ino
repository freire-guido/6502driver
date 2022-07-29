#include "busmanager.h"
#include "oscillator.h"

const int OSC = 10;
const int PH2 = 11;
const int ADDR[8] = {2, 3, 4, 5, 6, 7, 8, 9};
// const int DATA[8] = {A5, A4, A3, A2, A1, A0, 12, 13};

void setup() {
  for (int address: ADDR) {
    pinMode(address, INPUT);
  }
  pinMode(PH2, INPUT);
  oscillate(1000000, OSC);
  Serial.begin(9600);
}

void loop() {
  unsigned int address = readBus(ADDR, 8);
  Serial.print(address, BIN); 
  Serial.print(' ');
  Serial.println(address, HEX);
  while (digitalRead(PH2) == LOW) {
    Serial.println();
  }
}