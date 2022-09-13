//タイヤの直径350mm

//timerloop
#include <FlexiTimer2.h>//(UNO)D3,D11&(MEGA)D9,D10のPWM出力は不可!!

//ホールセンサ
const int sensor_pin = 18;
int count = 0, count_old = 0; //カウント数
float distance = 0, velocity = 0; //距離、速度
float velocity2 = 0;//試験用
int digital_val = 0; //センサ値
int flag = 0;//状態切切替 0or1

//時間計測
unsigned long time_now, time_old;

void setup() {
  //外部割込みピン設定
  pinMode(sensor_pin, INPUT_PULLUP);
  attachInterrupt(5, sensor_count2, CHANGE);
  //timerlooop設定
  FlexiTimer2::set(5, timerloop);
  FlexiTimer2::start();
  //シリアル通信設定
  Serial.begin(9600);
  Serial.println("start");
}

void loop() {

}


void timerloop() {
  distance = count * 1.099;
  //velocity = (count-count_old) * 791.28;
  velocity = (count - count_old) * 1099 * 0.72;
  count_old = count;

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

  Serial.print("velocity2:");
  Serial.print(velocity2);
  Serial.println("ms");
}
