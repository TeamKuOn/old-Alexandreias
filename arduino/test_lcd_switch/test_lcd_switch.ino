#include <Wire.h>            // Arduino IDE のI2Cライブラリ
#include <LcdCore.h>         // LCDコアライブラリ
#include <LCD_ACM1602NI.h>   // 秋月I2C液晶用のI/Oライブラリ

LCD_ACM1602NI lcd(0xa0); // 0xa0はI2Cアドレス

#define START_PIN 2
#define STOP_PIN 3
#define RESET_PIN 4
#define SPEED_SET_PIN A1

unsigned long time;
unsigned long time_lap = 0;
unsigned long time_lap_old = 0;

int c = 0; //count

void setup() {
  //ピン設定
  pinMode(START_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);

  //LCD設定
  lcd.begin(16, 2);//横0-15、縦0-1
  lcd.print("set_up");

  //シリアル通信設定
  Serial.begin(9600);
  Serial.println("start");

  //タイム計測スタート
  time = millis() / 1000;
  Serial.print("time:");
  Serial.println(time);
}

void loop() {
  time = millis() / 1000;
  c += 1;
  Serial.print("c:");
  Serial.print(c);
  Serial.print("\t");
  time_lap_display(c, 0, 0);


  //表示
  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print("L:");


  if (switch_read() == 1) {
    Serial.println("START_PIN");
    lcd.setCursor(0, 1);
    lcd.print("START:");
  }

  if (switch_read() == 2) {
    Serial.println("STOP_PIN");
    lcd.setCursor(0, 1);
    lcd.print("STOP:       ");
  }

  if (switch_read() == 3) {
    Serial.println("RESET_PIN");
    time_lap_old = time;
    lcd.setCursor(0, 1);
    lcd.print(time_lap);
  }

  //ラップタイム計算
  time_lap = time - time_lap_old;

}

int switch_read() { //return -1,1to4
  if (digitalRead(START_PIN) == HIGH && digitalRead(STOP_PIN) == LOW && digitalRead(RESET_PIN) == LOW) {//100
    return 1;
  }

  if (digitalRead(START_PIN) == LOW && digitalRead(STOP_PIN) == HIGH && digitalRead(RESET_PIN) == LOW) {//010
    return 2;
  }

  if (digitalRead(START_PIN) == LOW && digitalRead(STOP_PIN) == LOW && digitalRead(RESET_PIN) == HIGH) {//001
    return 3;
  }

  //  Serial.println("switch_read()_error");
  return -1;//エラー値

}

int set_speed() {
  int speed_value = analogRead(SPEED_SET_PIN) / 10.23;//[%]
  int quotient = speed_value / 5; //商
  int remainder = speed_value % 5; //余り

  if (remainder > 0) {
    speed_value = (quotient * 5) + 5; //[km/h]
  } else {
    speed_value = (quotient * 5); //[km/h]
  }

  return speed_value;
}

void time_lap_display(int time_input, int coordinate0, int coordinate1) {
  static int h, m;
  h = time_input / 60;
  m = time_input % 60;

  lcd.setCursor(coordinate0, coordinate1);
  if (h < 10) {
    lcd.print("0");
    lcd.print(h);
    Serial.print("0");
    Serial.print(h);

  } else if (h < 60) {
    lcd.print(h);
    Serial.print(h);

  } else {
    lcd.print("over");
    Serial.print("over");
  }

  if (time_input >= 3600) {
    Serial.println("");
  } else if (m < 10) {
    lcd.print(":0");
    lcd.print(m);
    Serial.print(":0");
    Serial.println(m);

  } else if (m < 60) {
    lcd.print(":");
    lcd.print(m);
    Serial.print(":");
    Serial.println(m);
  }
}
