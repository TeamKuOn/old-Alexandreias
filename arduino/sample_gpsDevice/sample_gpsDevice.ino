#include <TinyGPS++.h>
static const uint32_t GPSBand = 9600;

// The TinyGPS++ object
// TinyGPSPlus gps;
TinyGPSPlus neo6m;
#define GpsSerial Serial1     // Tx1(18), RX(19)

void setup() {
  Serial.begin(115200);
  GpsSerial.begin(GPSBand);
  Serial.println("GPS test....");

}

void loop() {
  while (GpsSerial.available() > 0){
    if (neo6m.encode(GpsSerial.read())){
      displayInfo();
      // Serial.println(neo6m.location.lat(), 6);
    }
  }

  if (millis() > 5000 && neo6m.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (neo6m.location.isValid())
  {
    Serial.print(neo6m.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(neo6m.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (neo6m.date.isValid())
  {
    Serial.print(neo6m.date.month());
    Serial.print(F("/"));
    Serial.print(neo6m.date.day());
    Serial.print(F("/"));
    Serial.print(neo6m.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (neo6m.time.isValid())
  {
    if (neo6m.time.hour() < 10) Serial.print(F("0"));
    Serial.print(neo6m.time.hour());
    Serial.print(F(":"));
    if (neo6m.time.minute() < 10) Serial.print(F("0"));
    Serial.print(neo6m.time.minute());
    Serial.print(F(":"));
    if (neo6m.time.second() < 10) Serial.print(F("0"));
    Serial.print(neo6m.time.second());
    Serial.print(F("."));
    if (neo6m.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(neo6m.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}