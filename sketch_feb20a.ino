#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>
//Simthobele Peter 221279288

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//IR Remote
int RECV_PIN = 2;

//Binary Counter
int counter = 0;
int maxCount = 9; // because CD4511 shows 0-9
int binaryPins[4] = {8, 9, 10, 11}; // LEDs + CD4511


#define BTN_UP     0xF50ABF00  // increase counter
#define BTN_DOWN   0xF708BF00  // decrease counter
#define BTN_RESET  0xF10EBF00  // reset counter

void setup() {
  Serial.begin(9600);

  //LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IR Counter Ready");

  // Binary pins setup
  for (int i = 0; i < 4; i++) {
    pinMode(binaryPins[i], OUTPUT);
  }

  // Start IR receiver
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("IR Code: ");
    Serial.println(code, HEX);

    if (code == BTN_UP) {
      counter++;
      if (counter > maxCount) counter = 0;
    }
    else if (code == BTN_DOWN) {
      counter--;
      if (counter < 0) counter = maxCount;
    }
    else if (code == BTN_RESET) {
      counter = 0;
    }

    updateOutputs();

    IrReceiver.resume();
  }
}

void updateOutputs() {
  // Show binary on LEDs and send BCD to CD4511
  for (int i = 0; i < 4; i++) {
    digitalWrite(binaryPins[i], (counter >> i) & 0x01);
  }

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Counter: ");
  lcd.print(counter);
  lcd.setCursor(0, 1);
  lcd.print("Binary: ");
  for (int i = 3; i >= 0; i--) {
    lcd.print((counter >> i) & 0x01);
  }
}
