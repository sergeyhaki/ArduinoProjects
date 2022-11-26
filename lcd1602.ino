#include <LiquidCrystal.h>
const int rs = 33, en = 32, d4 = 31, d5 = 30, d6 = 29, d7 = 28;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {  
  lcd.begin(16, 4);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 3); 
  lcd.print(millis() / 1000);
}
