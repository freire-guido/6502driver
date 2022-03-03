byte readBus(const int bus[8]) {
  byte res = 0;
  for (int i = 0; i < 8; i++) {
    pinMode(bus[i], INPUT);
    if (digitalRead(bus[i]) == HIGH) {
      res |= (1 << i);
    }
  }
  return (res);
}

void writeBus(const int bus[8], const byte data) {
  for (int i = 0; i < 8; i++) {
    pinMode(bus[i], OUTPUT);
    digitalWrite(bus[i], bitRead(data, i) == 1 ? HIGH : LOW);
  }
}