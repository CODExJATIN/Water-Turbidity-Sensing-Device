#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16x2 LCD
int redPin = 9;
int greenPin = 10;
int bluePin = 6;
int sensorPin = A0;

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("Water Turbidity");
  delay(2000);
  lcd.clear();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  lcd.clear();
  lcd.print("Turbidity: ");
  lcd.print(sensorValue);
  if (sensorValue < 300) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    lcd.print(" - Clear");
  } else if (sensorValue >= 300 && sensorValue < 600) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    lcd.print(" - Dirty");
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    lcd.print(" - Very Dirty");
  }
  delay(1000);
}
