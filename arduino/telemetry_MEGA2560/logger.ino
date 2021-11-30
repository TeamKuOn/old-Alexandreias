void writeDataLogger(){
	char payload[160];
  sprintf_P(payload, PSTR("{\"TimeStamp:\"{%s,%s},\"Location\":{%s,%s},%s, %s}"),
  							GpsJson.Date, GpsJson.Time, GpsJson.Latitude, GpsJson.Longitude, GpsJson.AltitudeKM, GpsJson.SpeedKMpH);

  CONSOLE.println(payload); // {"date":"2021-07-22","time":"15:03:36","latitude": 0.000000,"longitude":  0.000000,"Altitude":0}

  dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(payload);
    dataFile.close();

    CONSOLE.println(payload);
  } else {
    CONSOLE.println("error opening TELEMETRY_LOG.JSON");
    CONSOLE.println(dataFile);
  }

}