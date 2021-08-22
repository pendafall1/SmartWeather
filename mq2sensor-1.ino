#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2 ,1 ,0 , 4, 5, 6, 7, 3,POSITIVE);

int Gaz=A0;
int valeursensor;
void setup(){
    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Détecteur de gaz");
    delay(1000);
    pinMode(Gaz,InPut);
    serial.begin(9600);
}

void loop(){
    lcd.clear()
    int valeurSensor=analogRead(Gas);
    lcd.setcursor(0,0);
    lcd.print("Valeur :");
    lcd.print(valeurSensor);
    lcd.print("ppm");
    if(valeursensor>300){
        lcd.setcursor(0,1);
        lcd.print("WARNING: un gaz toxique a ete détecté veuillez aerer votre piéce ");
    }
    else{
        lcd.setcursor(0,1);
        lcd.print("Aucun de gaz toxique détecté");
}
    delay(200000);
}
