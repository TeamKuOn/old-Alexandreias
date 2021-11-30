void getSensorsData() {
  // get data form GPS NEO-6M Sensor
  getDateFromGps(GpsJson.Date, neo6m.date);     // get date
  getTimeFromGps(GpsJson.Time, neo6m.time);     // get time 
  dataAsFloatToChar(GpsJson.Latitude, "Latitude", neo6m.location.lat(), neo6m.location.isValid(), 11, 8);    // get latitude
  dataAsFloatToChar(GpsJson.Longitude, "Longitude", neo6m.location.lng(), neo6m.location.isValid(), 12, 8);    // get latitude

  dataAsFloatToChar(GpsJson.AltitudeKM, "Altitude", neo6m.altitude.kilometers(), neo6m.altitude.isValid(), 5, 3);    // get altitude
  dataAsFloatToChar(GpsJson.SpeedKMpH, "SpeedKMpH", neo6m.speed.kmph(), neo6m.speed.isValid(), 6, 3);    // get speed km / h
  dataAsBytToChar(GpsJson.HDOP, "HDOP", neo6m.hdop.value(), neo6m.hdop.isValid());    // get HDOP

}