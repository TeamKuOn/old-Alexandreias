/*
  This is LCD monitor output test code.
  we use arduino micro board
  LCD monitor: 1602A, Serial interface: 1602 serial interface
  
  [usage]    lcd.setCursor(0-19, 0-3);  (clomn, row)
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)

int i = 0;

void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}

void loop(){
  lcd.setCursor(0, 1);
  lcd.print("Int count: ");     lcd.print(i);
  i++;

  delay(1000);
}
