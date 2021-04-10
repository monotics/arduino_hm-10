#include <Arduino.h>
#include <SoftwareSerial.h>
#include "control.h"
#include "command.h"
 
#define MAX_SIZE 10
#define PIN_TX 9
#define PIN_RX 10

void sendCommand(const char * command);
void parseNext(int next);
bool isCommandFullyRead();

SoftwareSerial mySerial(PIN_TX, PIN_RX); // TX, RX

int buff[MAX_SIZE];
int currPos = 0;

void initBle() {
  mySerial.begin(9600);

  sendCommand("AT");
  sendCommand("AT+ROLE0"); // Role : Slave (Default)
  sendCommand("AT+UUID0xFFE0"); // Service UUID : 0xFFE0 (Default)
  sendCommand("AT+CHAR0xFFE1"); // Characteristic UUID : 0xFFE1 (Default)
  sendCommand("AT+NAMEBleTest"); // Device Name : "BleTest"
}

void sendCommand(const char * command) {
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(500);

  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("\nReply end");
  delay(100);
}

// Used for manual setup
void updateSerial() {
  if (mySerial.available())       
   Serial.write(mySerial.read()); 

  if (Serial.available())     
    mySerial.write(Serial.read());
}

void readBleCommand() {
  while (mySerial.available()) {
    int nc = mySerial.read();
    if (currPos > 0 || nc == CMD_START) {
        Serial.println(nc);
        parseNext(nc);
    }
  }
}

void parseNext(int next) {
  buff[currPos] = next;
  if (isCommandFullyRead()) {
    executeCommand(buff);
    currPos = 0;
  } else if (currPos < MAX_SIZE) {
    ++currPos;
  } else {
    Serial.println("Increase buffer size");
  }
}

bool isCommandFullyRead() {
  // [START|TYPE|LENGTH|DATA...]
  // command header is 3 bytes (START, Command type, num of parameters)
  // are all parameters already read
  return currPos >= BIT_LENGTH && buff[BIT_LENGTH] == currPos - BIT_LENGTH;    
}

void sendBleData(byte data) {
  mySerial.write(data);
  Serial.println(data);
}