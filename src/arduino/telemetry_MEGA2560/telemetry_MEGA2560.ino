/*
 *  This System is build by WASOU @_xwas0ux
 * 
 *  Telemetry System with Soracom using Arduino Due ATMEGA16I2
 *  Telemetry data send to Cloud via Unified Endpoint of SORACOM
 *  
 *  Selected Board - Arduino MEGA 2560
 * 
 *  Set Device and Sensor Pin setting
 *    [ LTE-M ]
 *      RX - 10
 *      TX - 11
 * 
 *    [ GPS NEO-6M ]
 *      RX1 - 19
 *      TX1 - 18
 * 
 *    [ SD Card Reader ]
 *      MOSI - pin 51
 *      MISO - pin 50
 *      CLK - pin 52
 *      CS - pin 53 (for MKRZero SD: SDCARD_SS_PIN)
 *      
 */

// Team identifer
// #define teamID xxxxxxxxx

//------------------ General communication setting ------------------
#include <Wire.h> 
#include <SoftwareSerial.h>

// dtostrf setting
// #include <avr/dtostrf.h>
// #include "dtostrf.h"

//------------------ Serial monitor setting ------------------
#define CONSOLE Serial
#define SerialBand  115200

//------------------ The GPS setting ------------------
#include <TinyGPS++.h>
TinyGPSPlus neo6m;
#define GpsSerial Serial1     // Tx1(18), RX(19), HardSerial
static const uint32_t GPSBand = 9600;
int recieveCount = 0;

//------------------ The barometer setting ------------------
//#include <Seeed_BMP280.h>
//BMP280 bmp280;    // isntantiation from barometer_BMP280

//------------------ Data Sending setting ------------------
// for LTE-M Shield for Arduino 
#define INTERVAL_MS (10000)
#define ENDPOINT "uni.soracom.io"
#define SKETCH_NAME "send_uptime_with_soracom"
#define VERSION "1.0"
#define RX 10
#define TX 11
#define BAUDRATE 9600
#define BG96_RESET 15
#define TINY_GSM_MODEM_BG96
#include <TinyGsmClient.h>
SoftwareSerial LTE_M_shieldUART(RX, TX);
// #define LTE_M_shieldUART Serial2
TinyGsm modem(LTE_M_shieldUART);
TinyGsmClient ctx(modem);
int sendCount = 0;

//------------------ Data logging setting ------------------
#include <SPI.h>
#include <SD.h>
const int chipSelect = 53;    // Arduino MEGA setting
File dataFile = SD.open("datalog.txt", FILE_WRITE);

//------------------ OLED display setting ------------------
// #include <U8x8lib.h>
// #define OLED u8x8
// U8X8_SSD1306_128X64_NONAME_HW_I2C OLED(/* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);
// #define U8X8_ENABLE_180_DEGREE_ROTATION 1

//------------------ structure setting ------------------
struct gpsNeo6mJson {
  char Date[30];
  char Time[30];
  char Latitude[30];
  char Longitude[30];
  char AltitudeKM[30];
  char SpeedKMpH[30];
  char HDOP[30];
};

struct barometerBmp280Json {
  char baromAlt;
};

struct gpsNeo6mJson GpsJson;
// struct barometerBmp280Json BaromJson;

////////////////////////////////////////////////////////////////////////////
//                            set up func.                                //
////////////////////////////////////////////////////////////////////////////
void setupConsole() { CONSOLE.begin(SerialBand); }

void setupGPS() { GpsSerial.begin(GPSBand); }

void setupLTE() {
  CONSOLE.print(F("Welcome to ")); CONSOLE.print(SKETCH_NAME); CONSOLE.print(F(" ")); CONSOLE.println(VERSION);

  CONSOLE.print(F("resetting module "));
  pinMode(BG96_RESET,OUTPUT);
  digitalWrite(BG96_RESET,LOW);
  delay(300);
  digitalWrite(BG96_RESET,HIGH);
  delay(300);
  digitalWrite(BG96_RESET,LOW);
  CONSOLE.println(F(" done."));

  LTE_M_shieldUART.begin(BAUDRATE);

  CONSOLE.print(F("modem.restart()"));
  modem.restart();
  CONSOLE.println(F(" done."));

  CONSOLE.print(F("modem.getModemInfo(): "));
  String modemInfo = modem.getModemInfo();
  CONSOLE.println(modemInfo);

  CONSOLE.print(F("waitForNetwork()"));
  while (!modem.waitForNetwork()) CONSOLE.print(".");
  CONSOLE.println(F(" Ok."));

  CONSOLE.print(F("gprsConnect(soracom.io)"));
  modem.gprsConnect("soracom.io", "sora", "sora");
  CONSOLE.println(F(" done."));

  CONSOLE.print(F("isNetworkConnected()"));
  while (!modem.isNetworkConnected()) CONSOLE.print(".");
  CONSOLE.println(F(" Ok."));

  CONSOLE.print(F("My IP addr: "));
  IPAddress ipaddr = modem.localIP();
  CONSOLE.println(ipaddr);

}


void setupSDCardReader(){
  SD.begin(chipSelect);

  // if (!SD.begin(chipSelect)) {
  //   Serial.println("Card failed, or not present");
  //   while (1);
  // }
  // Serial.println("card initialized.");

}

// void setupOLED() {
//   OLED.begin();
//   OLED.setFlipMode(U8X8_ENABLE_180_DEGREE_ROTATION);
//   OLED.setFont(u8x8_font_8x13B_1x2_f);

// }

void setup() {
  setupConsole();
  setupGPS();
  setupSDCardReader();
  setupLTE();
  // setupOLED();

  CONSOLE.println("Telemetry System started...");

}

void dataAsFloatToChar(char *pointer, char *jsonKey, double val, bool valid, int len, int decimal);
void getSensorsData();
void software_reset() { asm volatile ("  jmp 0"); }
void writeDataLogger();
void sendTelemetryData();

////////////////////////////////////////////////////////////////////////////
//                          main loop func.                               //
////////////////////////////////////////////////////////////////////////////
void loop() {
  while (GpsSerial.available() > 0){
    if (neo6m.encode(GpsSerial.read())) {
      CONSOLE.println("GPS is valid");
      // get data from sensors
      getSensorsData();

      // write data log to SD Card Reader
      // writeDataLogger();

    // } else {
      // CONSOLE.println("GPS is not valid...");
      }
  }

  if ((neo6m.time.second() % 30) == 0) {
    if (!sendCount > 0) {
      
      // send telemetry data with LTE-M
      LTE_M_shieldUART.listen();
      sendTelemetryData();
      CONSOLE.println("Data Send");
      sendCount++;

    } else {
      sendCount = 0;
    }
  }
  // CONSOLE.println("Loop()");
  // GpsSerial.listen();
}

// static void smartDelay(unsigned long ms) {
//   unsigned long start = millis();
//   do {
//     while (GpsSerial.available())
//       neo6m.encode(GpsSerial.read());

//   } while (millis() - start < ms);
// }
