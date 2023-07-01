#include <HID-Project.h>

int statusVol;

void setup() {
  // Initialize Consumer API
  Consumer.begin();
  pinMode(8, INPUT);
  pinMode(1, INPUT);
  statusVol = analogRead(1);  
}

void loop() {

  int btnStatus = analogRead(8);
  int newStatusVol = analogRead(1);
  int diff = newStatusVol - statusVol;
   
  Serial.println(btnStatus);
  if (btnStatus >= 500){
      Consumer.write(MEDIA_VOL_MUTE);
  }
  if (diff < 0)
  {
    Consumer.write(MEDIA_VOL_DOWN);
  }else if (diff > 0)
  {
    Consumer.write(MEDIA_VOL_UP);
  }
  delay(1000);
}
