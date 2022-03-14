#include "busmanager.h"
#include "oscillator.h"

const int PH = 2;
const int OSC = 3;
const int ADDR[16] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, A0, A1, A2, A3, A4, A5};

bool serviced = false;

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(ADDR[i], INPUT);
  }
  pinMode(PH, INPUT);
  oscillate(1000000, 3);
  Serial.begin(115200);
  Serial.println("RDY");
}

void loop() {
  unsigned int address = readBus(ADDR, 16);
  Serial.print(address, BIN); 
  Serial.print(' ');
  Serial.println(address, HEX);
  while (digitalRead(PH) == LOW) {}
}