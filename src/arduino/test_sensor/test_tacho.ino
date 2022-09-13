/*
  test tacho meter pulse
  we use arduino micro
*/

const int analogInPin = 9;  

// int analog_val = 0;  
int digital_val=0;      

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  analog_val = analogRead(analogInPin);
  digital_val= digitalRead(analogInPin);

  
  Serial.print(analog_val);
  Serial.print("\t");
  Serial.println(digital_val);
  delay(500);  
}
