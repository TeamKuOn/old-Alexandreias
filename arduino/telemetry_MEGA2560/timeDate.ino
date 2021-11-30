void getDateFromGps(char *pointer, TinyGPSDate &d) {
  char dateBuff[32];
  if (!d.isValid()){
    sprintf(dateBuff, "\"2000-00-00\"");
    // CONSOLE.print(dateBuff);
  
  } else {
    sprintf(dateBuff, "\"%02d-%02d-%02d\"", d.year(), d.month(), d.day());
    // CONSOLE.print(dateBuff);

  }
  sprintf(pointer, "\"date\":%s", dateBuff);
  // CONSOLE.println(pointer);
}

void getTimeFromGps(char *pointer, TinyGPSTime &t) {
    char timeBuff[32];
  if (!t.isValid()) {
    sprintf(timeBuff, "\"00:00:00\"");
  
  } else {
    sprintf(timeBuff, "\"%02d:%02d:%02d\"", t.hour() + 9, t.minute(), t.second());
    // CONSOLE.print(timeBuff);

  }
  sprintf(pointer, "\"time\":%s", timeBuff);
  // CONSOLE.println(pointer);
}
