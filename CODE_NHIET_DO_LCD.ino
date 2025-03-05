#include "DHT.h"

#define DHTPIN 2   //Chân kết nối với chân DHT11 là chân D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int setnhiet = 35;
int setgas = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
dht.begin();
lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
float t = dht.readTemperature();
int gas = map(analogRead(A0),600,1020,100,0);
if(gas >= 100) gas = 100;
if(gas <= 0) gas = 0;
if(t >= setnhiet && gas >= setgas){
  lcd.setCursor(0, 0);
  lcd.print("   CANH BAO!    ");
  lcd.setCursor(0, 0);
  lcd.print("NGUY CO CHAY CAO");
}
else{
if(t >= setnhiet){
  lcd.setCursor(0, 0);
  lcd.print("NHIET DO QUA CAO");
}
else {
  lcd.setCursor(0, 0);
  lcd.print("NHIET DO:     *C");
  lcd.setCursor(10, 0);
  lcd.print(t,1);
}

if(gas >= setgas){
  lcd.setCursor(0, 1);
  lcd.print(" RO RI KHI GAS  ");
}
else {
  lcd.setCursor(0, 1);
  lcd.print("KHI GAS:      *C");
  lcd.setCursor(10, 1);
  lcd.print(gas);
}

}
delay(300);
}
