#include "busmanager.h"
#include "oscillator.h"

const int CE = 10; // active low
const int WE = 11; // active low
const int ADDR[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int DATA[8] = {A5, A4, A3, A2, A1, A0, 12, 13};

const int offset = 0xFF00;

void setup() {
  pinMode(WE, OUTPUT);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, HIGH);
  digitalWrite(WE, HIGH);
  Serial.begin(9600);
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
      digitalWrite(CE, LOW);
      digitalWrite(WE, LOW);
      writeBus(ADDR, 8, b + a);
      writeBus(DATA, 8, buffer[a]);
      digitalWrite(CE, HIGH);
      digitalWrite(WE, HIGH);

      writeBus(ADDR, 8, b + a);
      writeBus(DATA, 8, 0);
      digitalWrite(CE, LOW);
      byte read = readBus(DATA, 8);
      if (read != buffer[a]) {
        Serial.print("ERR: ");
        Serial.println(b + a);
      }
    }
    b += 16;
    j = message.indexOf('\n', j + 1);
  }
  Serial.println("DONE!");
}
