/*
  This is LCD monitor output test code.
  we use arduino micro board
  LCD monitor: 1602A, Serial interface: 1602 serial interface
  
  [usage]    lcd.setCursor(0-19, 0-3);  (clomn, row)

* [Sample for 20 × 4 Display]
*              1111111111
*    01234567890123456789  -> x
*    ____________________
* 0 | SPLIT / LAP  |SPEED| <-- Guidance
* 1 |   0:18:42:152| 60.0| <== SPLIT TIME | Speed (km/h)
* 2 |03 0:01:25:532| KM/H| <-- LAP TIME 
* 3 |#####-###  x1000 rpm| <-- Tachometer Bar
* |  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
* v
* y
*/

#include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)
LiquidCrystal_I2C lcd(0x27, 20, 4); // 半田ブリッジ -> 1 1 1 (All Open)

float i = 0;
char buf[10];

void display_absolute_char(){
  lcd.setCursor(1, 0);
  lcd.print("SPLIT / LAP");

  lcd.setCursor(14, 0);
  lcd.print("|SPEED");

  lcd.setCursor(14, 1);
  lcd.print("|");

  lcd.setCursor(14, 2);
  lcd.print("| km/h");

  lcd.setCursor(11, 3);
  lcd.print("x1000 rpm");
}

void setup() {
  lcd.init(); 
  lcd.backlight();
  display_absolute_char();
}

void loop(){
  lcd.setCursor(19, 1);
  sprintf(buf, "%3.1f", i);
  lcd.print(buf);
  i++;

  delay(1000);
}
