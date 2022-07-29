unsigned int readBus(const int bus[], const int _sz) {
  unsigned int res = 0;
  for (int i = 0; i < _sz; i++) {
    pinMode(bus[i], INPUT);
    res |= (unsigned int) digitalRead(bus[i]) << i;
  }
  return(res);
}

void writeBus(const int bus[], const int _sz, const int data) {
  for (int i = 0; i < _sz; i++) {
    pinMode(bus[i], OUTPUT);
    digitalWrite(bus[i], bitRead(data, i) == 1 ? HIGH : LOW);
  }
}

void strToBytes(String str, byte buff[], int _sz, char delim = ' ') {
  int i = 0;
  int j = str.indexOf(delim);
  for (int b = 0; b < _sz && j != -1; b++) {
    buff[b] = str.substring(i, j).toInt();
    i = j;
    j = str.indexOf(delim, j + 1);
  }
}