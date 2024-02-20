#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "String.h"

#define D1     18

char arm[] = "ARM0N";
char launch[] = "LAUNCH";
char arm_off[] = "ARMOFF";
RF24 radio(7, 8); // CE, CSN
typedef enum {                                            //State Machine Init
  SAFE,
  ARMED,
  LAUNCHED,
  FAILURE
} STATE;

STATE currentState = SAFE;
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  switch(currentState){
  case SAFE:
  if(strcmp(text,arm) == 0){
  curretState = ARMED;
  }
  break;
  case ARMED:
  if(strcmp(text,lauch) == 0){
  curretState = LAUNCHED;
  }
  if(strcmp(text,arm_off) == 0){
  curretState = SAFE;
  }
  break;
  case LAUCHED:
  digitalWrite(D1,  HIGH);    //D4184 is pulled HIGH, POWERING LOAD
  break;
  }
}
