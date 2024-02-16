//ramin
//import all required libraries
#include <Wire.h>
#include <Arduino.h>
// #include <Strings.h>

#define ADDR_Ax 0b000  //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

void writeI2CByte(byte data_addr, byte data);
byte readI2CByte(byte data_addr);

byte data_write[80] = { 0, 1, 2, 3, 5 };
uint8_t _read_data = 0;
uint8_t _write_data = 0;
byte addres_A = 0;

char dataincomingchar[6];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  // writeI2CByte(0, 1);
  // Serial.println(readI2CByte(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    // incomingByte = Serial.readString();
    // incomingByte = readStringUntil();
    String incomingString = Serial.readStringUntil('\n');

    switch (incomingString[0]) {
      case 'a':
        Serial.print("I received: ");
        Serial.println(readI2CByte(addres_A));
        break;
      case 'b':
        if (incomingString[1] != NULL) {
          // writeI2CByte(0, data_write[(int)incomingString[1]]);
          //  int myInt=incomingString[1].toInt();
          for(int i = 0; i < 5; i++) {
            if (incomingString[i]==NULL) break;
            dataincomingchar[i]= incomingString[i+1];
          }
          int myInt = atoi(dataincomingchar);
          writeI2CByte(addres_A, myInt);

          Serial.print("writed: ");
          //Serial.println(dataincomingchar);
          Serial.println(myInt);
        }
        break;
    }


    // say what you got:
    // Serial.print("I received: ");
    // // Serial.println(incomingByte, DEC);
    // Serial.println(incomingString);
  }
}

void writeI2CByte(byte data_addr, byte data) {
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr) {
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1);  //retrieve 1 returned byte
  delay(10);
  if (Wire.available()) {
    data = Wire.read();
  } else {

    data = 250;
  }
  return data;
}