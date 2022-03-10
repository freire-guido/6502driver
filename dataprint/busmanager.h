int readBus(const int bus[], const int _sz) {
  int res = 0;
  for (int i = 0; i < _sz; i++) {
    pinMode(bus[i], INPUT);
    if (digitalRead(bus[i]) == HIGH) {
      res |= (1 << i);
    }
  }
  return(res);
}

void writeBus(const int bus[], const byte data) {
  for (int i = 0; i < 8; i++) {
    pinMode(bus[i], OUTPUT);
    digitalWrite(bus[i], bitRead(data, i) == 1 ? HIGH : LOW);
  }
}

void printBus(const int bus[], const int _sz) {
  int data = readBus(bus, _sz);
  Serial.print(data, BIN);
  Serial.print(' ');
  Serial.println(data, HEX);
}