void epeper_1_updata() {
  digitalWrite(epaper_ctrl_no, LOW);
  epd_clear();
  //Bluetooth.println("System ready!");
  //tmElements_t tm;

  int humd = myHumidity.readHumidity();
  int temp = myHumidity.readTemperature();
  // TEMP = DHT.temperature;
  //Serial.println( DHT.temperature);
  // HUMI = DHT.humidity;
  //Serial.println( DHT.humidity);
  sprintf(buff, "TEMP:%02d C R.H.:%02d %%", temp, humd );
  Serial.println(buff);

  epd_disp_bitmap("PIC1.BMP", 120, 130);
  sprintf(buff, "TEMP :  %02d", temp);
  epd_disp_string(buff, 250, 200);
  epd_disp_bitmap("PIC5.BMP", 480, 200);

  epd_disp_bitmap("PIC2.BMP", 120, 300);
  sprintf(buff, "R.  H.   :  %02d    %%", humd );
  epd_disp_string(buff, 250, 370);

  call_rtc();

  epd_udpate();
  delay(100);
}
void epeper_2_updata() {
  digitalWrite(epaper_ctrl_no, HIGH);
  epd_clear();
  buff_count = 0;
  while (Serial.available()) {
    show_string[buff_count] = Serial.read();
    show_string[buff_count + 1] = 0;
    buff_count++;
    Serial.print(show_string[buff_count]);



  }
  //Serial.print(show_string);

  if (show_string[0] == '*' && show_string[1] == 's' && show_string[2] == 'm' && show_string[3] == 'i' && show_string[4] == 'l' && show_string[5] == 'e') {
    epd_disp_bitmap("PIC8.BMP", 100, 100);
  } else if (show_string[0] == '*' && show_string[1] == 'P' && show_string[2] == '1') {
    epd_disp_bitmap("P1.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'P' && show_string[2] == '2') {
    epd_disp_bitmap("P2.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'P' && show_string[2] == '3') {
    epd_disp_bitmap("P3.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'P' && show_string[2] == '4') {
    epd_disp_bitmap("P4.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'P' && show_string[2] == '5') {
    epd_disp_bitmap("P5.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'C' && show_string[2] == 'H' ) {
    epd_disp_bitmap("GO.BMP", 100, 50);
  } else if (show_string[0] == '*' && show_string[1] == 'S' && show_string[2] == 'H' && show_string[5] == 'S' && show_string[6] == 'M' ) {
    int int_timer=0;
    Serial.println("Set Time");
    //buff_time=strcpy(show_string[3],show_string[4])
    buff_time = (show_string[3]-48)*10 + show_string[4]-48;
    //Serial.println(buff_time);
    tm.Hour = buff_time.toInt();
    buff_time =(show_string[7]-48)*10 + show_string[8]-48;
    //Serial.println(buff_time);
    tm.Minute = buff_time.toInt();
    /*
      tm.Hour = show_string[3];
      tm.Minute = show_string[6];
    */
    RTC.write(tm);
    show_string[0] = 'O';
    show_string[1] = 'K';
    show_string[2] = 0;
  }

  else  {
    sprintf(buff, "%s", show_string);
    epd_disp_string(buff, 50, 280);
  }
  epd_udpate();
  delay(100);
}
