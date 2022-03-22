#include "busmanager.h"
#include "oscillator.h"

const int ADDR[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int SELT[6] = {A0, A1, A2, A3, A4, A5};

void setup() {
    for (int select: SELT) {
        pinMode(select, OUTPUT);
    }
}

void loop() {
    if (readBus(ADDR, 8) == 0xFF) {
        digitalWrite(SELT[0], HIGH);
    } else if (readBus(ADDR, 8) == 0xC0) {
        digitalWrite(SELT[1], HIGH);
    } else {
        for (int select: SELT) {
            digitalWrite(select, LOW);
        }
    }
}