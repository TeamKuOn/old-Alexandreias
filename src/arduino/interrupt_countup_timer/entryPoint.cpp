/*
  This code is Build by WASOU @_xwas0ux

  Thsi is timer count up and LCD monitor output test code.
  we use arduino micro board.

  < Attention >
      Timer/Counter0 is already used by delay() and millis(), 
    so, you have to use Timer/Counter1,   Timer/Counter3, and Timer/Counter4.

  LCD monitor: 1602A, Serial interface: 1602 serial interface
  
  [usage]    lcd.setCursor(0, 0);  (clomn, row)

 * Copyright <2020> <LightningBrains> 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "std_arduino.hpp"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)
                 
// Const
const byte LED_PIN = 13;
// const byte INPUT_PIN = 7;
const byte LAP_PIN = 5;
const char LIGHTNING_BRAINS[] = {"LightningBrains"};

// Global
byte ledState = LOW;
unsigned long msTime;
 
int hh = 0;
int mm = 0;
int ss = 0;
int ms = 0;

void lcdSetup(){
  lcd.init(); 
  lcd.backlight();

}

void setup() {
  pinMode(LED_PIN, OUTPUT);      // On-Board LED
  pinMode(LAP_PIN, INPUT);
 
  lcdSetup();
//   setCursor(1, 0);          // 表示位置 1, 0
//   sendText(LIGHTNING_BRAINS, strlen(LIGHTNING_BRAINS));
//   Serial.begin(115200);

  TCCR1A = 0b00000000;  // Mode4(MGM10=0,MGM11=0) CTC
  TCCR1B = 0b00001011;  // Mode4(MGM12=1,MGM13=0):clkI/64 (From prescaler)
  // TIMSK1 = 0b00000000;          // Timer OFF
  TIMSK1 = 0b00000010;         // Timer ON
  OCR1A = 250;
 
  // 割り込み設定：入力ピン、割り込みハンドラ、割り込み条件はHIGH→LOW
  // スイッチに使用した 5 pin は割り込み処理に対応していないため，使用不可
  // attachInterrupt(digitalPinToInterrupt(LAP_PIN), switchON, FALLING);
  msTime = millis();
  // Serial.println(msTime);
  lcd.setCursor(2, 0);
  lcd.print("Timer start..");
}
 
char  buf[18];            // 表示バッファ

void loop() {
  // Display count up time
  // sprintf(buf, "%02d:%02d:%02d.%03d", hh, mm, ss, ms);
  sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
  lcd.setCursor(2, 1);
//   sendText(buf, strlen(buf));
//   lcd.print(buf, strlen(buf));
  lcd.print(buf);
}
 
// タイマー割り込みハンドラ
//   IMPUT_PIN HIGH→LOW
//
ISR(TIMER1_COMPA_vect) {
  // Count Up timer 
  ++ms;
  if(ms > 999) {
    ledState = !ledState;         // LED tuggle 
    digitalWrite(LED_PIN, ledState);

    ms = 0;
    ++ss;
    if(ss > 59) {
      ss = 0;
      ++mm;

      if(mm > 59) {
        mm = 0;
        ++hh;

        if(hh > 23) {
          hh = 0;
          mm = 0;
          ++hh;
        
          if(hh > 23)
            hh = 0;
        }
      }
    }
  }
}
 
// スイッチ割り込みハンドラ
//   IMPUT_PIN HIGH→LOW
//
// void switchON() {
//   if((millis() - msTime) > 50) {
//     if(TIMSK1 == 0b00000000) {
//       TIMSK1 = 0b00000010;  // OCIE1A: Timer/Countern, Output Compare A Match Interrupt Enable
//     }
//     else {
//       TIMSK1 = 0b00000000;  // OCIE1A: Timer/Countern, Output Compare A Match Interrupt Disable
//     }
//     TCNT1 = 0;
//     msTime = millis();
//   }
// }
