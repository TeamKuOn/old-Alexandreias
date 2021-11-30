/////////////////////////////////////////////////////////////////////////
//  float data formatting as json foramt
//   <usage>
//         dataAsFloatToChar(gpsLatitude, "latitude", GpsSerial.location.lat(),     
//                                             GpsSerial.location.isValid(), 9, 6);
/////////////////////////////////////////////////////////////////////////
void dataAsFloatToChar(char *pointer, char *jsonKey, double val, bool valid, int len, int decimal) {
  char bufValue[15];
  if (valid) {
    dtostrf(val, len, decimal, bufValue); // float => string

  } else {
    float bufEmpty = 00.000000;
    dtostrf(bufEmpty, len, decimal, bufValue); // float => string
    // CONSOLE.println(bufEmpty);

  }
  sprintf(pointer, "\"%s\":%s", jsonKey, bufValue);
  // CONSOLE.println(pointer);
}

// int data formatting as json format
void dataAsBytToChar(char *pointer, char *jsonKey, byte val, bool valid) {
  sprintf(pointer, "\"%s\":%d", jsonKey, val);
  // CONSOLE.println(pointer);
}
