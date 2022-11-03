#include "Arduino.h"
#include "led.h"


Led::Led(int led) {
  pinMode(led, OUTPUT);
  _led = led;


}

void Led::sendHeartBeat() {
  if(millis() - heartBeatTime >= heartBeatInterval ) {
    if(heartBeatOn == false) {
      digitalWrite(_led, HIGH);
      heartBeatOn = true;
    } else {
      digitalWrite(_led, LOW);
      heartBeatOn = false;
    }
    heartBeatTime = millis();
  }
}