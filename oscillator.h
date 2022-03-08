void oscillate(unsigned int freq, int out) {
    pinMode(out, OUTPUT);
    tone(out, freq);
}