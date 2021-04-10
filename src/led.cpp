#include <Arduino.h>

#define PIN_LED 3 // ~D3 (PWM)

void initLed() {
    pinMode(PIN_LED, OUTPUT);
}

/*
    LED On/Off
    sw :1 -> LED ON
    sw :0 -> LED OFF
*/
void ledSwitch(int sw) {
    digitalWrite(PIN_LED, sw);
}

/* Set LED brightness */
void ledDim(int value) {
    analogWrite(PIN_LED, value);
}

/* LED blinks {count} times */
void ledBlink(int count, int ms) {
    while (count-- > 0) {
        digitalWrite(PIN_LED, HIGH);
        delay(ms);
        digitalWrite(PIN_LED, LOW);
        delay(ms);
    }
}