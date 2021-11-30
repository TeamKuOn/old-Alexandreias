void sensor_count() {

  digital_val = digitalRead(sensor_pin);

  if (flag == 0 && digital_val == 0) {
    flag = 1;
  } else if (flag == 1 && digital_val == 1) {
    count++;
    flag = 0;
  }

}
void sensor_count2() {

  digital_val = digitalRead(sensor_pin);

  if (flag == 0 && digital_val == 0) {
    flag = 1;
  } else if (flag == 1 && digital_val == 1) {
    count++;
    time_now = millis();
    //Serial.print(time_now);
    velocity2 = 1.099 / ((time_now - time_old) * 1000); //timeの単位注意
    //    velocity2 =time_now - time_old;
    time_old = time_now;
    flag = 0;
  }

}
