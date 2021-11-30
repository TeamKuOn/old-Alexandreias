void sendTelemetryData(){
	char payload[160];
  sprintf_P(payload, PSTR("{\"TimeStamp:\"{%s, %s},\"Location\":{%s, %s}, %s, %s, %s}"),
  							GpsJson.Date, GpsJson.Time, GpsJson.Latitude, GpsJson.Longitude, GpsJson.AltitudeKM, GpsJson.SpeedKMpH, GpsJson.HDOP);

  CONSOLE.println(payload); // {"date":"2021-07-22","time":"15:03:36","latitude": 0.000000,"longitude":  0.000000,"Altitude":0}

// {
//     "teamID" : "oecu-kuon-jiykobo",
//     "timeStamp" : {
//         "date" : "2021-07-30",
//         "time" : "12:17:25"
//     },
//     "locationDeg" : {
//         "latitude" : 34.16623,
//         "longitude" : 136.153865
//     },
//     "altitudeMeter" : 125.7,
//     "totalMileage" : 1234,
//     "batteryEnergy" : {
//         "joules" : 123.4,
//         "volts" : 123.4,
//         "amperes" : 123.4
//     },
//     "solarEnergy" : {
//         "joules" : 123.4,
//         "volts" : 123.4,
//         "amperes" : 123.4
//     }
// } 

  CONSOLE.println(payload);

  CONSOLE.print(F("Send..."));
//   drawText_P(OLED, PSTR("Send..."));
  /* connect */
  if (!ctx.connect(ENDPOINT, 80)) {
    CONSOLE.println(F("failed."));
    // drawText_P(OLED, PSTR("failed."));
    delay(300);
    return;
  }
  /* send request */
  char hdr_buf[40];
  ctx.println(F("POST / HTTP/1.1"));
  sprintf_P(hdr_buf, PSTR("Host: %s"), ENDPOINT);
  ctx.println(hdr_buf);
  ctx.println(F("Content-Type: application/json"));
  sprintf_P(hdr_buf, PSTR("Content-Length: %d"), strlen(payload));
  ctx.println(hdr_buf);
  ctx.println();
  ctx.println(payload);
  /* receive response */
  // NOTE: response header and body are ignore due to saving for memory
  ctx.stop();
  CONSOLE.println(F("done."));
//   OLED.clearLine(6);

  // delay(INTERVAL_MS);
#ifdef RESET_DURATION
  if(millis() > RESET_DURATION ) {
    CONSOLE.println("Execute software reset...");
    delay(1000);
    software_reset();

  }
#endif
}
