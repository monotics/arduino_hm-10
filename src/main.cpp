#include <Arduino.h>
#include "led.h"
#include "ble.h"

int prevData = 0;
unsigned long currTime;
unsigned long prevTime;

void setup() {
  Serial.begin(9600);
  initLed();
  initBle();
}

void loop() {
  // read command from central(ex:Android app)
  readBleCommand();

  // send analog value to central every 500ms
  currTime = millis();
  if(currTime - prevTime > 500) {
    prevTime = currTime;
    int data = analogRead(A0);
    data = map(data, 0, 1023, 0, 255);
    if (data != prevData) {
      sendBleData(data); // send 1 byte
      prevData = data;
    }
  }
}