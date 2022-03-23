#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial uart(10,11);

double latd,longd;
String response,link;
int stringlength = response.length();
int wktu=wktu;

void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LATD");
  lcd.setCursor(0,1);
  lcd.print("LONGD");
  Serial.begin(9600);
  Serial.println("GPS STARTED");
  uart.begin(9600);  
  uart.println("AT+CMGF=1");
  Serial.println("COMPLETED");
  uart.println("AT+CNMI=2,2,0,0,0"); 
} 

void loop(){
 if (uart.available()>0){
  response = uart.readStringUntil('\n');
  }
     
 if(stringlength != response.length()){
  baca();
  if(response.indexOf("LOCATION")!=-1){
    uart.println("AT+CMGF=1"); 
    delay(wktu);  
    uart.println("AT+CMGS=\"0895341617835\"\r"); 
    delay(wktu);
    uart.println(link);d
    delay(100);
    uart.println((char)26);
    delay(wktu);
    }
  else{
    uart.println("AT+CMGF=1");
    delay(wktu); 
    uart.println("AT+CMGS=\"081373832944\"\r");
    delay(wktu);
    uart.println("ERROR");
    delay(100);
    uart.println((char)26);
    delay(wktu);
  }
 }
 lcd();
}

void baca(){
  if(Serial.available()) {
    gps.encode(Serial.read());
  }
  if(gps.location.isUpdated()) {
    latd = gps.location.lat();
    longd = gps.location.lng();
    link = "www.google.com/maps/place/" + String(latd, 6) + "," + String(longd, 6) ;
    Serial.println(link);
  }
}
void lcd(){
  lcd.setCursor(4,0);
  lcd.print(latd);
  lcd.setCursor(5,0);
  lcd.print(latd);
  delay(wktu);
}
