/*
  Thsi is timer count up and LCD monitor output test code.
  we use arduino micro board.

  < Attention >
      Timer/Counter0 is already used by delay() and millis(), 
    so, you have to use Timer/Counter1,   Timer/Counter3, and Timer/Counter4.
*/

const byte LED_PIN = 13;
byte ledState = LOW;
 
void setup() {
  pinMode(LED_PIN, OUTPUT);      // On-Board LED
 
  TCCR1A = 0b00000000;  // Mode4(MGM10=0,MGM11=0) CTC
  TCCR1B = 0b00001100;  // Mode4(MGM12=1,MGM13=0):clkI/256 (From prescaler)
  TIMSK1 = 0b00000010;  // OCIE1A: Timer/Countern, Output Compare A Match Interrupt Enable
  OCR1A = 62500;
}
 
ISR(TIMER1_COMPA_vect) {
  ledState = !ledState;         // LEDをトグル動作
  digitalWrite(LED_PIN, ledState);
}
 
void loop() {
}