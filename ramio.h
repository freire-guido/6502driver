#include "busmanager.h"

struct RAM {
    const int* addr;
    const int* data;
    int ce, we, start;
    RAM(const int* a, const int* d, int c, int w, int s = 0): addr{a}, data{d}, ce{c}, we{w}, start{s} {};
    bool read(const int ad) const {
        digitalWrite(we, HIGH);
        digitalWrite(ce, LOW);
        writeBus(addr, 16, start + ad);
        byte readval = readBus(data, 8);
        digitalWrite(ce, HIGH);
        digitalWrite(we, HIGH);
        return readval;
    }
    bool write(const int ad, const byte da, bool checkerr = true) const {
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