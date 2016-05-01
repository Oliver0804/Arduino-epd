/*********************************************************************************************************

  File                : Arduino-epd
  Hardware Environment:
  Build Environment   : Arduino
  Version             : V1.6.1
  By                  : WaveShare

                                   (c) Copyright 2005-2015, WaveShare
                                        http://www.waveshare.net
                                        http://www.waveshare.com
                                           All Rights Reserved

*********************************************************************************************************/
#include <epd.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "SI7013.h"
#define epaper_ctrl_no 10
SI7013 myHumidity;
tmElements_t tm;

int TEMP = 0;
int HUMI = 0;
char show_string[] = "HI~Pls,keyin anything!!";
int buff_count = 0;
String buff_time = "";
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
  pinMode(epaper_ctrl_no, OUTPUT);



  digitalWrite(epaper_ctrl_no, HIGH);
  delay(100);
  epd_init();
  epd_wakeup();
  epd_set_ch_font(GBK64);
  epd_set_en_font(ASCII64);
  epd_set_memory(MEM_TF);
  epd_clear();
  epd_load_pic();
  epd_disp_string("123", 250, 200);
  Serial.println("Waiting E-paper 1.");

  delay(100);
  digitalWrite(epaper_ctrl_no, LOW);
  delay(100);
  epd_init();
  epd_wakeup();
  epd_set_ch_font(GBK64);
  epd_set_en_font(ASCII64);
  epd_set_memory(MEM_TF);
  epd_clear();
  epd_load_pic();
  epd_disp_string("456", 250, 200);
  Serial.println("Waiting E-paper 2.");

  delay(100);
  change_display();
  call_rtc();
  digitalWrite(epaper_ctrl_no, HIGH);
  epd_disp_bitmap("GO.BMP", 100, 50);
  epd_udpate();
  digitalWrite(epaper_ctrl_no, LOW);
  epd_disp_bitmap("GO.BMP", 100, 50);
  epd_udpate();
  delay(5000);
  Serial.println("System ready!");
  delay(5000);
}

void loop(void)
{

  epeper_1_updata();
  epeper_2_updata();
  delay(5000);
}


