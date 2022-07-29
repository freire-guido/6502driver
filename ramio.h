#include "busmanager.h"

struct RAM {
    const int addr[16];
    const int data[8];
    const int ce;
    const int we;
    const int start = 0;
    bool werror = false;
    bool read(const int ad) {
        digitalWrite(we, HIGH);
        digitalWrite(ce, LOW);
        writeBus(addr, 16, start + ad);
        byte readval = readBus(data, 8);
        digitalWrite(ce, HIGH);
        digitalWrite(we, HIGH);
        return readval;
    }
    bool write(const int ad, const byte da, bool checkerr = true) {
        digitalWrite(we, LOW);
        digitalWrite(ce, LOW);
        writeBus(addr, 16, start + ad);
        writeBus(data, 8, da);
        digitalWrite(ce, HIGH);
        digitalWrite(we, HIGH);
        if (checkerr) {
            writeBus(addr, 8, start + ad);
            writeBus(data, 8, 0x00);
            return read(ad) == da;
        }
    }
};