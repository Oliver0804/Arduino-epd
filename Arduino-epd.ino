/*********************************************************************************************************
*
* File                : Arduino-epd
* Hardware Environment:
* Build Environment   : Arduino
* Version             : V1.6.1
* By                  : WaveShare
*
*                                  (c) Copyright 2005-2015, WaveShare
*                                       http://www.waveshare.net
*                                       http://www.waveshare.com
*                                          All Rights Reserved
*
*********************************************************************************************************/
#include <epd.h>
#include <dht.h>
#define dht_dpin 7
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "SI7013.h"

SI7013 myHumidity;
dht DHT;

int TEMP = 0;
int HUMI = 0;
char show_string[] = "HI~Pls,keyin anything!!";
int buff_count = 0;

#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 11); // RX, TX
char buff[] = {0};
void setup(void)
{
  Bluetooth.begin(9600);
  myHumidity.begin();

  Serial.begin(9600);
  Serial.println("System ready!");
  Bluetooth.println("System ready!");
  epd_init();
  epd_wakeup();
  epd_set_ch_font(GBK64);
  epd_set_en_font(ASCII64);
  epd_set_memory(MEM_TF);
  epd_clear();
  epd_load_pic();
  epd_clear();
  call_rtc();
  delay(5000);
}

void loop(void)
{
  //Bluetooth.println("System ready!");
  tmElements_t tm;

  int humd = myHumidity.readHumidity();
  int temp = myHumidity.readTemperature();



  // TEMP = DHT.temperature;
  //Serial.println( DHT.temperature);
  // HUMI = DHT.humidity;
  //Serial.println( DHT.humidity);
  sprintf(buff, "TEMP:%02d C R.H.:%02d %%", temp, humd );

  Serial.println(buff);
  epd_clear();
  epd_disp_bitmap("PIC1.BMP", 20, 30);
  epd_disp_bitmap("PIC2.BMP", 20, 210);
  epd_disp_bitmap("PIC5.BMP", 490, 110);
  sprintf(buff, "DHT_TEMP :  %02d", temp);
  epd_disp_string(buff, 150, 100);
  sprintf(buff, "DHT_R.  H.   :  %02d    %%", humd );
  epd_disp_string(buff, 150, 280);
  buff_count = 0;
  while (Serial.available()) {
    show_string[buff_count] = Serial.read();
    show_string[buff_count + 1] = 0;
    //Serial.print("*");
    //Serial.print(show_string[buff_count]);
    //Serial.print(show_string[buff_count]);
    buff_count++;
  }
  buff_count = 0;
  Bluetooth.listen();
  while (Bluetooth.available()) {
    show_string[buff_count] = Bluetooth.read();
    show_string[buff_count + 1] = 0;
    //Serial.print(show_string[buff_count]);
    //Serial.print(show_string[buff_count]);
    buff_count++;
  }

  sprintf(buff, "%s", show_string);
  epd_disp_string(buff, 50, 450);
  call_rtc();
  epd_udpate();





  delay(60000);
}


