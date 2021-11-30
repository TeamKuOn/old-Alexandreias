//SPI通信で使われるピンは次のとおりです。
//Arduino Uno(ATmega168/328を搭載するボード): 10(SS)、11(MOSI)、12(MISO)、13(SCK)
//Arduino Leonardo: ICSP4(MOSI)、ICSP1(MISO)、ICSP3(SCK)
//Arduino Mega: 50(MISO)、51(MOSI)、52(SCK)、53(SS)

//モータ制御(SPI通信)
#include <SPI.h>
byte address = 0x00;
int CS = 53;

void setup() {
  //モータ制御(SPI通信設定)
  pinMode (CS, OUTPUT);
  SPI.begin();
}

void loop() {
  digitalPotWrite(0);
  //  for (int i = 255; i >= 0; i--)
  //  {
  //    digitalPotWrite(i);
  //    delay(20);
  //  }
  delay(500);
  //  for (int i = 0; i <= 255; i++)
  //  {
  //    digitalPotWrite(i);
  //    delay(20);
  //  }
  delay(500);


}

int digitalPotWrite(int value) {

  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);

}
