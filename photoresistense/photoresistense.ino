#include "LiquidCrystal_I2C.h"
#define LDR A1  // composante photoresistor sur la pin A1
#define LEDV 5   // composante led sur la pin 9
#define LEDJ 6
#define LEDR 7
#define BUZZ 8
unsigned int value;
unsigned int lum;
 LiquidCrystal_I2C LCD1(0x27, 16, 2);
void setup() {
   // initialise la communication avec le PC
   Serial.begin(9600);
 LCD1.init();
   // initialise les broches
   pinMode(LEDV, OUTPUT);
    pinMode(LEDJ, OUTPUT);
     pinMode(LEDR, OUTPUT);
      pinMode(BUZZ, OUTPUT);
   pinMode(LDR, INPUT);
}
 
void loop() {
  LCD1.setBacklight(1);
   // mesure la tension sur la broche A1
   value = analogRead(LDR);
   Serial.println(value);

   // allume la LED
if (value<800){
  lum = 35;
}
    if (value>800 && value<990) {
      lum = 75;
    }
    if (value>990){
      lum = 76;
    }
   if (lum == 35) {
    digitalWrite(LEDV, HIGH);
     digitalWrite(LEDJ, LOW);
      digitalWrite(LEDR, LOW);
      digitalWrite(BUZZ, LOW);
        LCD1.clear();
               LCD1.setBacklight(1); 
                LCD1.setCursor(0, 0);
                LCD1.print("LUMINOSITE");
                LCD1.setCursor(3, 1);
                LCD1.print("FORTE");
   }
   
    if (lum == 75) {
      digitalWrite(LEDV, LOW);
      digitalWrite(LEDJ, HIGH);
      digitalWrite(LEDR, LOW);
      digitalWrite(BUZZ, LOW);
      LCD1.clear();
               LCD1.setBacklight(1); 
                LCD1.setCursor(0, 0);
                LCD1.print("LUMINOSITE");
                LCD1.setCursor(3, 1);
                LCD1.print("MOYENNE");
      
    }

   /*/  if (lum == 75) {
      
      digitalWrite(BUZZ, HIGH);
      delay(5000);
         digitalWrite(BUZZ, LOW);
           delay(5000);
    }*/
    
    
if (lum == 76) {
digitalWrite(LEDR, HIGH);
digitalWrite(BUZZ, HIGH);
  digitalWrite(LEDV, LOW);
      digitalWrite(LEDJ, LOW);
        LCD1.clear();
               LCD1.setBacklight(1); 
                 LCD1.setCursor(0, 0);
                LCD1.print("LUMINOSITE");
                LCD1.setCursor(3, 1);
                LCD1.print("FAIBLE");

}

   // désactiver la LED
  // if (value>600) digitalWrite(LED, LOW);

   delay(200);
}
