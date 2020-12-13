#include <Arduino.h>
#include <EEPROM.h>

int address = 13; // EEPROM ADDRESS

// 2 digits =  16 - 255  =  239
// 3 digits = 256 - 4095 = 3839
int start =  16;
int end   = 255;

long randNumber;
long serialNumber;

void readUID();
void writeUID();

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // check EEPROM serial number
  if (EEPROM.read(address) != 255){
    EEPROM.get(address, serialNumber);
    if (serialNumber >= start && serialNumber <= end){
      readUID();
    } else {
      writeUID();
    }
  } else {
    writeUID();
  }
  delay(20000);
}

void readUID() {
  // get serial number
  Serial.println("[UID]: Reading ...");
  //EEPROM.get(address, serialNumber);
  Serial.print("SN: ");
  Serial.print(serialNumber); 
  Serial.print(" - HEX: ");
  Serial.println(String(serialNumber,HEX));
}

void writeUID() {
  // generate random number
  randNumber = random(start,end);
  Serial.println("[UID]: Generating ...");
  Serial.print("RN: ");
  Serial.print(randNumber);
  Serial.print(" -> HEX: ");
  Serial.println(String(randNumber,HEX));
  EEPROM.put(address, randNumber);
}