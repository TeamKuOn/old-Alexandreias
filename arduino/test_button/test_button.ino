
/*
  This code is Build by WASOU @_xwas0ux

  This is LCD monitor output test code.
  we use arduino micro board
  LCD monitor => 4 * 20 char, Serial interface: 1602 serial interface
  
  [usage]    lcd.setCursor(20, 4);  (clomn, row)(max)
*/

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)

// Button setting
const int LAP_btn = 5;
const int Page_btn = 6; 

// LED toggle setting
const int ledPin =  13;

// variables will change:
int  LAP_state = 0;
int  Page_state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(LAP_btn, INPUT);
  pinMode(Page_btn, INPUT);
  
  LAP_state = digitalRead(LAP_btn);
  lcd.setCursor(0, 0);
  lcd.print(LAP_state);

  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 3);
  lcd.print("Button test");
}

// LAP_state = digitalRead(LAP_btn);
// Page_state = digitalRead(Page_btn);

// int mode_flag = 0;
int btnCharge = 0;
int switchState = 0;

int LongCheckBtn(){
  switchState = digitalRead(LAP_btn);     // check button status

  if ((LAP_state == LOW) && (switchState == LOW)) {
    // mode_flag = 0;

  } else if ((LAP_state == LOW) && (switchState == HIGH)) {
    LAP_state = HIGH;
    return 0;

  } else if ((LAP_state == HIGH) && (switchState == HIGH)) {
    ++btnCharge;
    return 0;

  } else if ((LAP_state == HIGH) && (switchState == LOW)) {
    if (btnCharge > 35) {
      return 2;

    } else if (btnCharge <= 35) {
      return 1;
                
    }
    LAP_state = LOW;
    btnCharge = 0;

  }
  
    // t = millis();
    // ++btnCharge;

    // if (LAP_state == LOW) {
      // if (btnCharge > 100) {
      //   mode_flag = 2;
      //   btnCharge = 0;
    
      // } else if (btnCharge <= 20) {
      //   mode_flag = 1;
      //   btnCharge = 0;

      // } else {
      //   mode_flag = 1;
      //   btnCharge = 0;
      // }

    // } else {
    //   mode_flag = 0;

    // }
  // }

  // if (Page_state == HIGH) {
  //   // turn LED on:
  //   digitalWrite(ledPin, HIGH);
  //   lcd.setCursor(0, 2);
  //   lcd.print("PAGE: HIGH ");
  // } else {
  //   // turn LED off:
  //   digitalWrite(ledPin, LOW);
  //   lcd.setCursor(0, 2);
  //   lcd.print("PAGE: LOW  ");
  // }

}   // end of LongCheckBtn()

void loop() {
  // Page_state = digitalRead(Page_btn);
  // LongCheckBtn();
  lcd.setCursor(18, 3);
  lcd.print(btnCharge);
  lcd.setCursor(0, 0);
  lcd.print(LAP_state);
  lcd.setCursor(2, 0);
  lcd.print(switchState);
  lcd.setCursor(4, 0);
  lcd.print(mode_flag);

  switch (LongCheckBtn()) {
    case 0:
      digitalWrite(ledPin, LOW);
      lcd.setCursor(0, 1);
      lcd.print("LAP: LOW        ");   
      break;

    case 1:
      digitalWrite(ledPin, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("LAP: HIGH      ");
      break;

    case 2:  
      digitalWrite(ledPin, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("LAP: LONG HIGH");
      break;

    default:
      break;
  }

}

// intterupt button setting
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27,16,2);   // 半田ブリッジ -> 1 1 1 (All Open)

// const int LAP_PIN = 5;
// int i = 0;

// void btnCount(){
//   lcd.print("LAP: "); lcd.print(i);

// }

// void setup() {
//   pinMode(LAP_PIN, INPUT_PULLUP);

//   lcd.init(); 
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Button test");

//   attachInterrupt(digitalPinToInterrupt(LAP_PIN), btnCount, RISING);
// }

// void loop(){
//   // lcd.setCursor(0, 1);
//   // lcd.print("Int count: ");     lcd.print(i);
//   // i++;

//   // delay(1000);
// }
