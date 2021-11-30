//タイヤの直径350mm ,1回転16パルス
int i = 0;
//timerloop
#include <FlexiTimer2.h>//(UNO)D3,D11&(MEGA)D9,D10のPWM出力は不可!!

//ホールセンサ
const int sensor_pin = 18;
unsigned long count = 0; //カウント数
float distance = 0.0, distance_old = 0.0, velocity = 0.0; //距離、速度
float velocity_diff = 0.0, velocity_old = 0.0;
float _velocity_old[5] = {0.0, 0.0, 0.0, 0.0, 0.0}; //速度平均関数用(average_speed)
int digital_val = 0; //センサ値
int flag = 0;//状態切切替 0or1

//モータ制御(SPI通信)
//Arduino Mega: 50(MISO)、51(MOSI)、52(SCK)、53(SS)
#include <SPI.h>
byte address = 0x00;
const int CS = 53;
const double kp = 5, ki = 1, kd = 1; //PIDゲイン
double duty, pduty, iduty, dduty;

//時間計測
unsigned long time_now, time_old;

void setup() {
  //ホールセンサ(外部割込みピン設定)
  pinMode(sensor_pin, INPUT_PULLUP);
  attachInterrupt(5, sensor_count, CHANGE);
  //モータ制御(SPI通信設定)
  pinMode (CS, OUTPUT);
  SPI.begin();
  //timerlooop設定
  FlexiTimer2::set(5, timerloop);
  FlexiTimer2::start();
  //シリアル通信設定
  Serial.begin(115200);
  Serial.println("start");
  //モータ出力
  for (int i = 0; i <= (int)255 / 4; i++) {
    digitalPotWrite(i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

void timerloop() {

  //計測
  //  distance = count * 1.099 / 16; //m
  distance = count * 0.0687; //m
  //  velocity = (distance - distance_old) * 200 * 3.6;
  distance_old = distance;

  //モータ制御
  pduty = kp * (10 - velocity);
  iduty = ki * 0;
  dduty = kd * 0;
  duty = pduty + iduty + dduty;
  if (duty < 0)duty = 0;

  //モータ出力
  digitalPotWrite(duty);

  //  for (int i = 0; i <= 50; i++)//加速
  //  {
  //    digitalPotWrite(i);
  //
  //  }
  //  for (int i = 255; i >= 0; i--)//減速
  //  {
  //    digitalPotWrite(i);
  //  }

  //  if (i > 255)i = 255;//加速
  //  digitalPotWrite(i);
  //  i++;

  //表示
  Serial.print("digital_val:");
  Serial.print(digital_val);
  Serial.print("\t");

  Serial.print("count:");
  Serial.print(count);
  Serial.print("\t");

  Serial.print("distance:");
  Serial.print(distance);
  Serial.print("m");
  Serial.print("\t");

  Serial.print("velocity:");
  Serial.print(velocity);
  Serial.print("km/h");
  //  Serial.print("\n");//改行

  Serial.print("duty:");
  Serial.print(duty);
  //  Serial.print("\t");
  //
  //  Serial.print("pduty:");
  //  Serial.print(pduty);
  //  Serial.print("\t");
  //
  //  Serial.print("iduty:");
  //  Serial.print(iduty);
  //  Serial.print("\t");
  //
  //  Serial.print("\t");
  //  Serial.print("dduty:");
  //  Serial.print(dduty);
  Serial.print("\n");//改行
}

float average_speed(int x) {
  float ave = 0.0;
  _velocity_old[5] = x;//今回入力

  for (int i; i >= 5; i++) {
    ave += _velocity_old[i];
    _velocity_old[i] = _velocity_old[i + 1];//次回分
  }
  ave = ave / 5;
  return ave;
}

void sensor_count() {

  digital_val = digitalRead(sensor_pin);

  if (flag == 0 && digital_val == 0) {
    flag = 1;
  } else if (flag == 1 && digital_val == 1) {
    count++;
    //    time_now = millis();
    time_now = micros();
    //    //Serial.print(time_now);
    //    velocity = 1.099 / ((time_now - time_old) * 1000); //timeの単位注意
    velocity = 247320 / (time_now - time_old); //timeの単位注意
    //    //        velocity = average_speed(velocity);//過去5回平均
    //    velocity = time_now - time_old;
    time_old = time_now;
    flag = 0;
  }

}

void digitalPotWrite(int value) {

  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);

}
