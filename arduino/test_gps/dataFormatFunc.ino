/////////////////////////////////////////////////////////////////////////
//  float data formatting as json foramt
//   <usage>
//         dataAsFloatToChar(gpsLatitude, "latitude", GpsSerial.location.lat(),     
//                                             GpsSerial.location.isValid(), 9, 6);
/////////////////////////////////////////////////////////////////////////
void dataAsFloatToChar(char *pointer, char *jsonKey, double val, bool valid, int len, int decimal) {
  Serial.print("Result: ");   Serial.println(pointer);
  Serial.print("json: ");   Serial.println(jsonKey);
  Serial.print("val: ");   Serial.println(val);
  Serial.print("valid: ");   Serial.println(valid);
  Serial.print("len: ");   Serial.println(len);
  Serial.print("decimal: ");   Serial.println(decimal);
  char bufValue[15];
  if (valid) {
    dtostrf(val, len, decimal, bufValue); // float => string
    Serial.print("bufValue: ");   Serial.println(bufValue);

  } else {
    float bufEmpty = 00.000000;
    dtostrf(bufEmpty, len, decimal, bufValue); // float => string
    Serial.println(bufEmpty);

  }
  sprintf(pointer, "\\\"%s\\\":%s", jsonKey, bufValue);
  Serial.print("pointer: ");   Serial.println(pointer);
}


// int data formatting as json format
void dataAsBytToChar(char *pointer, char *jsonKey, byte val, bool valid) {
  sprintf(pointer, "\"%s\":%d", jsonKey, val);
  // CONSOLE.println(pointer);
}