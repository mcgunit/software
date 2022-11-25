#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Custom modules
#include <led.h>

#define USB Serial
#define BMS Serial1

Servo esc;

int escPin = 2;
int throttleInput = A9;
int onBoardLed = 13;
int waterPump = 5;


unsigned long throttleValue = 0;
int throttlePercentage = 0;

unsigned long lastUpdateLCD = 0;
unsigned long lcdUpdateTime = 150;    // Time of update LCD screen in ms. To fast and it will not show correctly

int maxESC = 2200;




Led led(onBoardLed);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 characters and 2 line display


void setup() {
  USB.begin(115200);
  BMS.begin(115200);

  lcd.init();
  lcd.backlight();


  // Init esc
  esc.attach(escPin);
  esc.writeMicroseconds(1100);
  delay(1500);

  // Waterpomp
  pinMode(waterPump, OUTPUT);
  //digitalWrite(waterPump, HIGH);

}

void loop() {
  led.sendHeartBeat();

  // Analog read is 10-bit resolution.
  USB.print("Throttle input: ");
  USB.println(analogRead(throttleInput));

  throttleValue = map(analogRead(throttleInput), 266, 770, 1100, maxESC);
  if(throttleValue > maxESC) {
    throttleValue = maxESC;
  } else if(throttleValue < 1000) {
    throttleValue = 1000;
  }

  throttlePercentage = map(throttleValue, 1000, 1999, 0, 100);
  if(throttlePercentage > 100) {
    throttlePercentage = 100;
  } else if(throttlePercentage < 0) {
    throttlePercentage = 0;
  }
 
  // Esc control
  esc.writeMicroseconds(throttleValue);

  if(millis() - lastUpdateLCD > lcdUpdateTime) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Throttle: ");
    lcd.print(throttlePercentage);
    lcd.print(" %");
    lcd.setCursor(0,1);
    lcd.print("  ESC: ");
    lcd.print(throttleValue);
    lastUpdateLCD = millis();
  }
  

  //engineControl.setEngineDriveCoast(throttleValueint onBoardLed = 13;);
  
  delay(1);
}