#include "ramio.h"

const int ADDR[16] = {2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1};
const int DATA[8] = {A5, A4, A3, A2, A1, A0, 12, 13};

RAM ram(ADDR, DATA, 10, 11);

void setup() {
}

void loop() {}

void serialEvent() { 
  String message = Serial.readString();
  byte buffer[16];
  int b = 0;
  int j = message.indexOf('\n');
  Serial.println(message);
  for (int i = 0; i < message.length() && j != -1; i = j + 1) {
    strToBytes(message.substring(i, j), buffer, 16);
    for (int a = 0; a < 16; a++) {
      Serial.print(buffer[a]);
      Serial.print(' ');
      if (!ram.write(b + a, buffer[a])) {
        Serial.print("ERR: ");
        Serial.println(b + a);
      }
    }
    b += 16;
    j = message.indexOf('\n', j + 1);
  }
  Serial.println("DONE!");
}
