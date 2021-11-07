// Ce code est dedié au projet Smart Weather
// @ author: Khadim Mbacke Ndiaye
//Mesure de la qualite de l'air par un un capteur PM2.5 relié a un microcontrolleur esp32
//objectifs: Chercher le niveau de concentration de particules fine de type PM1.0, PM2.5 et PM10 dans une piece 

#include <WiFi.h>
#include "PMS.h"
#include <HardwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

PMS pms(Serial2);
PMS::DATA data;
 

String val1;
String val2;
String val3;

int relayPin = 23;
int buzzerPin = 15;

 
const char* ssid = "BambaWIFI";
const char* password = "********";
 
void Afficherlcd(int theLine, const char* theInfo, boolean clearFirst=true) {
  if (clearFirst) {
    lcd.clear();
  }
  lcd.setCursor(0, theLine);
  lcd.print(theInfo);
}  
 
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
 
 
   pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  
  lcd.begin(20, 4);
 
  lcd.home();
  lcd.print("Setup");
  Afficherlcd(0,"  Bienvenue", true);
  Afficherlcd(1,"    Baj3n", true);

  delay(500);
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  //Connexion Wifi
  WiFi.begin(ssid, password);
 
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  Afficherlcd(0," WiFi connected..!", true);
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  
  delay(4000);
 
 
}
 
void loop()
{
  if (pms.read(data))
  {
    val1 = data.PM_AE_UG_1_0;
    val2 = data.PM_AE_UG_2_5;
    val3 = data.PM_AE_UG_10_0;
 
    Serial.println("Moniteur de qualité de l'air");
 
    Serial.println("PM1.0 :" + val1 + "(ug/m3)");
 
    Serial.println("PM2.5 :" + val2 + "(ug/m3)");
 
    Serial.println("PM10  :" + val3 + "(ug/m3)");
 
    Serial.println("");
 
    lcd.clear();
    Afficherlcd(0," PM1.0: ", false);
    lcd.print(val1);
    lcd.print(" ug/m3");

    lcd.clear();
    Afficherlcd(2," PM2.5: ", false);
    lcd.print(val2);
    lcd.print(" ug/m3");

    lcd.clear();
    Afficherlcd(3," PM10 : ", false);
    lcd.print(val3);
    lcd.print(" ug/m3");
 
   
 
    
    delay(2000);
  }
  if (val2.toFloat() >= 150  || val3.toFloat() >= 50)
   
  {
    digitalWrite(relayPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    Afficherlcd(2,"Vous etes en danger l'air est pollué ", true);
     }
  
  else
  {
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
 }
