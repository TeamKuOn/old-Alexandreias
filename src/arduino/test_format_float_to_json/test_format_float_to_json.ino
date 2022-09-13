struct floatData {
  char jsonData1[30];
};


char *dataAsFloatToChar(char jsonKey[15], float val, bool valid, int len, int decimal) {
//  Serial.println(jsonKey);
//  Serial.println(val, 6);
//  Serial.println(valid);
//  Serial.println(len);
//  Serial.println(decimal);
  char returnBuf[30];
  char bufValue[15];
  if (valid) {
    dtostrf(val, len, decimal, bufValue); // float => string
//    Serial.println(bufValue);
  } else {
    float bufEmpty = 00.000000;
    dtostrf(bufEmpty, len, decimal, bufValue); // float => string
    Serial.println(bufEmpty);
  }
  sprintf(returnBuf, "'%s':%s", jsonKey, bufValue);
  Serial.println(returnBuf);
  return returnBuf;
}

void setup() {
  Serial.begin(115200);
//  char *buf = (char*)calloc(20, sizeof(char));
  char *buf[30];
//  Serial.println(buf);
  *buf = dataAsFloatToChar("latitude", 34.141825, true, 8, 6);
  Serial.println(*buf);
  *buf = dataAsFloatToChar("latitude", 34.141825, false, 8, 6);
  Serial.println(*buf);
}

void loop() {
  // put your main code here, to run repeatedly:
}
