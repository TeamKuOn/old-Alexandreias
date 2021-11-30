/*
  This code is Build by WASOU @_xwas0ux

  Pulse width measure.
  We use Arduino Micro Board.

*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)

unsigned long l_time = 0;
unsigned long h_time = 0;
unsigned long t_time = 0;

unsigned int pulseCount = 0;
unsigned int rotateCount = 0;
 
#define INPOUT_PIN 9

void setup() {
  pinMode(INPOUT_PIN, INPUT); // Setting at 9 pin 
  
  // lcd.init(); 
  // lcd.backlight();
  // lcd.setCursor(0, 0);
  // lcd.println("Pulse Counter   "); 

  Serial.begin(115200);
}
 
void loop() {
  h_time = pulseIn(INPOUT_PIN, HIGH); // Measure HIGH time at 9 pin and memory to "h_time" val. 
  l_time = pulseIn(INPOUT_PIN, LOW); // Measure LOW time at 9 pin and memory to "l_time" val. 
 
  t_time = h_time + l_time ; //  Culculate Pulse Width 

  // Display t_time
  // lcd.setCursor(0, 0);
  // lcd.print(t_time, DEC); // Print Frec. as DEC number to LCD Monitor. 
  Serial.println(t_time, DEC); // Print Frec. as DEC number to LCD Monitor. 

  // Display frec.
  // lcd.setCursor(0, 1);
  // lcd.print((1.0 / t_time) * 1000000 , DEC); // Print Frec. as DEC number to LCD Monitor. 
  Serial.println((1.0 / t_time) * 1000000 , DEC); // Print Frec. as DEC number to LCD Monitor. 

  // Display wheel rotate
  // lcd.setCursor(0, 1);
  // lcd.print(((1.0 / t_time) * 1000000) / 48, DEC); // Print Frec. as DEC number to LCD Monitor. 

}