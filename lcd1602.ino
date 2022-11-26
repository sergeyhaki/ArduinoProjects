#include <LiquidCrystal.h>
LiquidCrystal lcd(33, 32, 31, 30, 29, 28);  //rs, en, d4, d5, d6, d7  m128L version
//LiquidCrystal lcd(26, 27, 28, 29, 30, 31);  //rs, en, d4, d5, d6, d7  m64 version
//LiquidCrystal lcd(23, 22, 21, 20, 19, 18);  //rs, en, d4, d5, d6, d7 m16 version
 
void setup() {  
  lcd.begin(16, 4);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 3); 
  lcd.print(millis() / 1000);
}
