/*
 *  This code is build by WASOU @_xwas0ux
 * 
 *  You must install "Seeed_BMP280" library
*/

// #include <U8x8lib.h>
// U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
// #define U8X8_ENABLE_180_DEGREE_ROTATION 1

#include <Seeed_BMP280.h>
BMP280 bmp280;

#include <Wire.h> 
#define CONSOLE Serial
#define SerialBand  115200


struct barometer_bmp280 {
  char jsonFloat1[30];
  // char jsonFloat2[30];
};

struct barometer_bmp280 barom;

void dataAsFloatToChar(char *pointer, char *jsonKey, float val,     
                                 bool valid, int len, int decimal) {
//  CONSOLE.println(jsonKey);
//  CONSOLE.println(val, 6);
//  CONSOLE.println(valid);
//  CONSOLE.println(len);
//  CONSOLE.println(decimal);
  // char returnBuf[30];
  char bufValue[15];
  if (valid) {
    dtostrf(val, len, decimal, bufValue); // float => string
//    CONSOLE.println(bufValue);
  } else {
    float bufEmpty = 00.000000;
    dtostrf(bufEmpty, len, decimal, bufValue); // float => string
    CONSOLE.println(bufEmpty);
  }
  sprintf(pointer, "\\\"%s\\\":%s", jsonKey, bufValue);
  // \"Altitude\":12.3
  // CONSOLE.println(pointer);
  // return returnBuf;
}

// ---  use arduinojson lib ---
// void dataAsFloatToChar_jsonlib(char *pointer, char *jsonKey, float val, bool valid, int len, int decimal) {
//   // JSONVar myObject;

//   char bufValue[15];
//   if (valid) {
//     dtostrf(val, len, decimal, bufValue); // float data => string char
//     doc[*jsonKey] = bufValue;
// //    CONSOLE.println(bufValue);
//   } else {
//     float bufEmpty = 00.000000;
//     dtostrf(bufEmpty, len, decimal, bufValue); // float => string
//     doc[*jsonKey] = bufEmpty;
//     CONSOLE.println(bufEmpty);
//   }
//   // myObject[jsonKey] = val;
//   // CONSOLE.println(myObject);
//   // *pointer = myObject;
//   // pointer = JSON.stringify(myObject);
//   // sprintf(pointer, "%s:%s", jsonKey, bufValue);
//   // "Altitude":12.3
//   serializeJson(doc, CONSOLE);
//   CONSOLE.println(pointer);
//   // return returnBuf;
// }


void setup() {
  CONSOLE.begin(SerialBand);
  if(!bmp280.init()){
    CONSOLE.println("Device error!");
  }
}

// void loop()
// {
//   float pressure;
  
//   //get and print temperatures
//   CONSOLE.print("Temp: ");
//   CONSOLE.print(bmp280.getTemperature());
//   CONSOLE.println("C"); // The unit for  Celsius because original arduino don't support speical symbols
  
//   //get and print atmospheric pressure data
//   CONSOLE.print("Pressure: ");
//   CONSOLE.print(pressure = bmp280.getPressure());
//   CONSOLE.println("Pa");
  
//   //get and print altitude data
//   CONSOLE.print("Altitude: ");
//   CONSOLE.print(bmp280.calcAltitude(pressure));
//   CONSOLE.println("m");
  
//   CONSOLE.println("\n");//add a line between output of different times.

//   delay(1000);
// }

void loop() {
  // struct barometer_bmp280 barom;
  // if (!) {
  //   /* code */
  // }
  
  // CONSOLE.println("Air Pres. DEMO");
  // u8x8.begin();
  // u8x8.setFlipMode(U8X8_ENABLE_180_DEGREE_ROTATION);
  // u8x8.setFont(u8x8_font_8x13B_1x2_f);
  // u8x8.setCursor(0, 0);
  // u8x8.print("Air Pres. Demo.");
  // u8x8.setCursor(0, 2);
  // u8x8.print("VALUE:");
  // if (!bmp280.init()) {
  //   CONSOLE.println("Device error!!");
  // } else {
  //   CONSOLE.println("Device reading...");
  // }
  // StaticJsonBuffer<200> jsonBuffer;

  // CONSOLE.println("-- default function --");
  // float pressure = bmp280.getPressure();
  // float altitude = bmp280.calcAltitude(pressure);
  // CONSOLE.print("Use print");    CONSOLE.println(altitude);
  // char buf1[10];
  // dtostrf(altitude, 5, 1, buf1); /* format from float/double to str "99.9" */
  // char buf2[12];
  // sprintf(buf2, "\"Altitude\":%s [m]", buf1);
  // CONSOLE.print("Use print");   CONSOLE.println(buf2);

  // CONSOLE.println();
  CONSOLE.println("-- user function --");
  dataAsFloatToChar(barom.jsonFloat1, "Altitude", bmp280.calcAltitude(bmp280.getPressure()), true, 5, 1);
  CONSOLE.println(barom.jsonFloat1);    //"Altitude":-20.7
  delay(500);

  // CONSOLE.println("-- use ArduinoJson lib function --");
  // dataAsFloatToChar_jsonlib(barom.jsonFloat2, "Altitude", bmp280.calcAltitude(bmp280.getPressure()), true, 5, 1);
  // CONSOLE.println(barom.jsonFloat2);
  // delay(500);

}
