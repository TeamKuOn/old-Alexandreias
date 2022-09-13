//タイヤの直径350mm
const int Pin = A0;
int digital_val = 0;

int count = 0;
int flag = 0;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {

  digital_val = digitalRead(Pin);

  if (flag == 0 && digital_val == 0) {
    flag = 1;
  } else if (flag == 1 && digital_val == 1) {
    count++;
    flag = 0;
  }


  Serial.print(digital_val);
  Serial.print("\t");
  Serial.println(count);

}
