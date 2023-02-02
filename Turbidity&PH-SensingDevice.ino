#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1015 ads; 
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16x2 LCD
int redPin = 9;
int greenPin = 10;
int bluePin = 6;
int sensorPin = A0;
int pH_sensor_pin = A1;
float voltage = 0.0;
float pH = 0.0;

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("Water Monitoring");
  delay(2000);
  lcd.clear();
  ads.begin();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  voltage = ads.readADC_SingleEnded(pH_sensor_pin) * (5.0 / 32768.0);
  pH = -5.70 * voltage + 14.00;
  lcd.clear();
  lcd.print("Turbidity: ");
  lcd.print(sensorValue);
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pH);
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
