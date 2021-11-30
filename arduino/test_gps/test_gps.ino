/*
  This code is Build by WASOU @_xwas0ux

  This is GPS & data formatting test code.
  We use Arduino MEGA 2560 board.
*/
#include <TinyGPS++.h>
static const uint32_t GPSBand = 9600;

// The TinyGPS++ object
// TinyGPSPlus gps;
TinyGPSPlus neo6m;
#define GpsSerial Serial1     // Tx1(18), RX(19)
// #include <SoftwareSerial.h>
// #define RX1 19
// #define TX1 18
// SoftwareSerial GpsSerial (RX1, TX1);

// structure setting
struct gpsNeo6mJson {
  char Date[30];
  char Time[30];
  char Latitude[30];
  char Longitude[30];
  char Altitude[30];
  char HDOP[30];
};

struct gpsNeo6mJson GpsJson;

void dataAsFloatToChar(char *pointer, char jsonKey, double val, bool valid, int len, int decimal);

void getSensorsData() {
  // get data form GPS NEO-6M Sensor
  dataAsFloatToChar(GpsJson.Latitude, "latitude", neo6m.location.lat(), neo6m.location.isValid(), 10, 6);    // get latitude
  // dataAsFloatToChar();    // get longitude
  // dataAsFloatToChar();    // get altitude 
}

void setup() {
  Serial.begin(115200);
  GpsSerial.begin(GPSBand);
  Serial.println("GPS test....");

}

void loop() {
  // GpsSerial.listen();
  // delay(1000);
  while (GpsSerial.available() > 0) {
    if (neo6m.encode(GpsSerial.read())) {
      Serial.println("---------------------------------------------------");
      // getSensorsData();

      // Serial.print("Result: ");   Serial.println(GpsJson.Latitude);
      // Serial.print("Result: ");   Serial.println(GpsJson.Altitude);

      Serial.println(neo6m.location.lat(), 8);
      Serial.println(neo6m.location.lng(), 8);
      Serial.println(neo6m.altitude.kilometers());
      Serial.println(neo6m.hdop.value()); 
      dataAsBytToChar(GpsJson.HDOP, "HDOP", neo6m.hdop.value(), neo6m.hdop.isValid());    // get HDOP
      Serial.println(GpsJson.HDOP);
      // GpsJson.Latitude = neo6m.location.lat();
      // Serial.println(latitude);
      // Serial.println(neo6m.location.lat(), 6);
      // Serial.println(neo6m.location.isValid());
      // Serial.println(neo6m.location.lat(), 6);
      // Serial.println(neo6m.location.lng(), 6);

    // delay(500);
    } else {
      Serial.println("GPS signal is not Valid...");
    }
  }
  Serial.println("Loop()");
}

/*
void loop()
{
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
*/
