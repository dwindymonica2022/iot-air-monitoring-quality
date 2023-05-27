#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h> //library dari NodeMCU ESP8266 WiFi
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);

int measurePin = A0;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  lcd.print("mulai");
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("Sensor Debu");
  delay(400);
  lcd.setCursor(0,1);
  lcd.print("Pengukuran Debu");
  delay(400);
  lcd.clear();
}

void loop(){
//  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

//  if ( dustDensity < 0)
//  {
//    dustDensity = 0.00;
//  }

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  Serial.println("Voltage:");
  Serial.println(calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(dustDensity);

  delay(1000);

  voMeasured = analogRead(measurePin);
  lcd.clear(); 



  lcd.setCursor(0,1);
  lcd.print("RSV : ");
  delay(50);
  lcd.setCursor(6,1);
  lcd.print(voMeasured);
  delay(1000);

  lcd.setCursor(0,0);
  lcd.print("Volt :");
  delay(50);
  lcd.setCursor(6,0);
  lcd.print(calcVoltage);
  delay(1000);

  lcd.setCursor(0,0);
  lcd.print("Dust :");
  delay(50);
  lcd.setCursor(6,0);
  lcd.print(dustDensity);
  delay(1000);

   while (voMeasured > 30){
    voMeasured = analogRead(measurePin);
    lcd.clear();
    digitalWrite(ledPower, HIGH);
    lcd.setCursor(0,0);
    lcd.print("POLUSI TINGGI");
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("MENJAUH!!!!");
    delay(200);
   }
    delay(200);
    
}
