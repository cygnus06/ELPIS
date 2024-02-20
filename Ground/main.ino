
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int KeyLED = 38;
const int ArmLED = 37;
const int LaunchLED = 35;
const int KEY_PIN = 29;
const int ARM_PIN = 28;
const int LAUNCH_PIN = 33;

// States present in the FSM.
typedef enum {
  KEY,
  ARM,
  LAUNCH,
} States;

States Current_state = KEY;        //Initial state of the board is KEY.

void setup(){
  pinMode(KeyLED, OUTPUT);
  pinMode(ArmLED, OUTPUT);
  pinMode(LaunchLED, OUTPUT);
  pinMode(KEY_PIN, INPUT_PULLDOWN); //Configured input pulldown to ensure no floating value.
  pinMode(ARM_PIN, INPUT_PULLDOWN);
  pinMode(LAUNCH_PIN, INPUT_PULLDOWN);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
  Serial1.begin(9600);              //Xbee serial communication using Serial1. 
}

void loop(){
  switch (Current_state) {
    case KEY:
      digitalWrite(KeyLED,HIGH);  //Initial state KEY hence KeyLED it will remain HIGH.
      if (digitalRead(ARM_PIN) == HIGH) {
        digitalWrite(ArmLED,HIGH);
        Current_state = ARM;      //If ARM pin has been switched ON then Current_State changes to ARM.
        char arm_arr[] = "ARMON";
        Serial.println("Current state = ARM");
        radio.write(&arm_arr, sizeof(arm_arr));  //If not working try message.
        delay(1000);              //Delays are necessary when transmitting to avoid debouncing issues when reading toggle pin state.
      }
      break;

    case ARM:
      if (digitalRead(LAUNCH_PIN) == HIGH) {
        digitalWrite(LaunchLED,HIGH);
        Current_state = LAUNCH;    //If LAUNCH pin has been switched ON then Current_State changes to LAUNCH.
        char launch_arr[] = "LAUNCH";
        Serial.println("Current state = LAUNCH");
        radio.write(&launch_arr, sizeof(launch_arr));  //If not working try message.
      }

      if (digitalRead(ARM_PIN) == LOW) {
        digitalWrite(ArmLED,LOW);
        Current_state = KEY;       //If ARM pin has been switched OFF then Current_State changes back to KEY.
        char arm_arr_low[] = "ARMON";
        Serial.println("Current state = KEY");
        radio.write(&arm_arr_low, sizeof(arm_arr_low));  //If not working try message.
      }
      delay(1000);                //Delays are necessary when transmitting to avoid debouncing issues when reading toggle pin state.
      break;

    case LAUNCH: 
      if(Serial1.available()>0){
      String output = Serial1.readStringUntil('\n');
      }
      break;

    default:
      break;
  }
}
