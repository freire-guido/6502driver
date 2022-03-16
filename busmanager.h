unsigned int readBus(const int bus[], const int _sz) {
  unsigned int res = 0;
  for (int i = 0; i < _sz; i++) {
    pinMode(bus[i], INPUT);
    res |= (unsigned int) digitalRead(bus[i]) << i;
  }
  return(res);
}

void writeBus(const int bus[], const byte data) {
  for (int i = 0; i < 8; i++) {
    pinMode(bus[i], OUTPUT);
    digitalWrite(bus[i], bitRead(data, i) == 1 ? HIGH : LOW);
  }
}