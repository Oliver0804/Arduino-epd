
void call_rtc() {
  if (RTC.read(tm)) {

    Serial.print("Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.println("");

    epd_disp_bitmap("PIC9.BMP", 350, 65);
    sprintf(buff, "%02d     :     %02d", tm.Hour, tm.Minute);
    epd_disp_string(buff, 450, 70);
    
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
