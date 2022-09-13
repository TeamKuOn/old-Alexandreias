#define START_PIN 2
#define STOP_PIN 3
#define RESET_PIN 4
#define SPEED_SET_PIN A1

unsigned long time;
unsigned long time_lap = 0;
unsigned long time_lap_old = 0;

void setup() {
  //ピン設定
  pinMode(START_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);

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

  if (switch_read() == 1) {
    Serial.println("START_PIN");
  }

  if (switch_read() == 2) {
    Serial.println("STOP_PIN");
  }

  if (switch_read() == 3) {
    Serial.println("RESET_PIN");
    time_lap_old = time;
  }

  //ラップタイム計算
  time_lap = time - time_lap_old;

  //表示
  Serial.print("time:");
  Serial.print(time);

  Serial.print("\t");
  Serial.print("time_lap");
  Serial.print(time_lap);

  Serial.print("\t");
  Serial.print("switch_read[-1,1to4]");
  Serial.print(switch_read());

  Serial.print("\t");
  Serial.print("set_speed[km/h]");
  Serial.println(set_speed());
}

int switch_read() { //-1,1to4
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
