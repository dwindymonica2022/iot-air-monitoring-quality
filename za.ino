//kelompok1

#define BLYNK_PRINT Serial //mendefinisikan serial dari blynk
#include <SPI.h>
#include <Wire.h> 
#include <ESP8266WiFi.h> //library dari NodeMCU ESP8266 WiFi
#include <BlynkSimpleEsp8266.h> //ini juga
#include <DHT.h> //Library dari sensor DHT11 (sensor suhu))
#include <LiquidCrystal_I2C.h>

// Dapetin tokennya di email
char auth[] = "adV9agT374GRs3CzGdjGk1bk4Fp-xLMT";

// id dan password internet
char ssid[] = "muzaaa";
char pass[] = "oy12oy12";
#define DHTPIN 2          // Digital pin 4
#define DHTTYPE DHT11     // tipe sensor suhu yg dipakai adalah DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

//SimpleTimer timer;
int mq135 = A0;
int gas_data = 0;

int buzzer = 13;
int led = 12;


void setup(){ //di bawah ini perintah untuk menjalankan semua komponen
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(gas_data, INPUT);
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, getSendData);
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  lcd.print("mulai");
  delay(100);
    lcd.setCursor(0,0);
  lcd.print("Pendeteksian Gas");
  delay(400);
  lcd.setCursor(0,1);
  lcd.print("Pengukuran Gas");
  delay(400);
  lcd.clear();
}

void loop(){
  timer.run();
  Blynk.run();

  gas_data = analogRead(mq135);
  noTone(buzzer);
  lcd.clear(); 



  lcd.setCursor(0,0);
  lcd.print("GAS : ");
  delay(50);
  lcd.setCursor(6,0);
  lcd.print(gas_data);
  lcd.print("PPM");
  delay(1000);
  
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);

   while (gas_data > 500){
    gas_data = analogRead(mq135);
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    tone(buzzer, 1000, 10000);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("GAS BERBAHAYA");
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("MENJAUH!!!!");
    delay(200);
   }
    delay(200);
    
}

void getSendData(){
  gas_data = analogRead(mq135);
  Blynk.virtualWrite(V2, gas_data); //vpin v3
}

void sendSensor()
{
  float h = dht.readHumidity(); //membaca kelembaban di sekitar sensor
  float t = dht.readTemperature(); //membaca suhu di sekitar sensor

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);  //pin V5 untuk kelembaban
  Blynk.virtualWrite(V6, t);  //pin V6 untuk suhu
}
