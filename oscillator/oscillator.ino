int freq = 1000; // Hz
int out = 3;

void setup() {
    pinMode(out, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    tone(out, freq);
}