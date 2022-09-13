/*
 * main.cpp
 */
#include "stdArduino.hpp"
#include <Arduino_FreeRTOS.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

TimerHandle_t xMsec;

DHT dht(DHTPIN, DHTTYPE);

void xDHT11Callback(TimerHandle_t);

void setup() {
    Serial.begin(115200);
    Serial.println(F("DHT11 test!"));

    dht.begin();

    xMsec = xTimerCreate("DHT11", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, xDHT11Callback);
    xTimerStart(xMsec, 0);
}

void loop() {}

void xDHT11Callback(TimerHandle_t xTime){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
    }

}
