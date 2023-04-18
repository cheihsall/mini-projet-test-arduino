#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD1(0x27, 16, 2); // définit le type d'écran lcd 16 x 2
LiquidCrystal_I2C LCD2(0x27, 16, 2);

void setup() {
   LCD1.init(); // initialisation de l'afficheurs
   LCD2.init();
   LCD1.backlight();
   LCD2.backlight();
}

void loop() {
   LCD1.setCursor(1, 0);
   LCD1.print("I LOVE ARDUINO");
   LCD1.scrollDisplayLeft();

   LCD2.setCursor(8, 1);
   LCD2.print("HELLO WORLD");
   LCD2.scrollDisplayLeft();
  
   delay(300);
}
