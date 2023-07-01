#include <DHT_U.h>
#include <DHT.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 32      // OLED display height, in pixels

#define OLED_RESET     4      // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C   ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int RELE = 3;                 // DIGITAL PIN

void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  dht.begin();
  pinMode(RELE, OUTPUT);
}

void loop() {
  
  delay(500);
  
  float tempEnv = dht.readTemperature();
  float newTemp = float(analogRead(A6)) * 0.0375;
  newTemp = abs(newTemp - 30);
  int tempWish = int(newTemp);
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(2);
  display.print("T:");
  display.setCursor(64,0);
  display.print(tempEnv);
  display.setCursor(0,16);
  display.print("D:");
  display.setCursor(64,16);      
  display.print(tempWish); 

  if (tempEnv < float(tempWish)) {
    digitalWrite(RELE, HIGH);
  }else if (tempEnv >= (tempWish + 1)){
    digitalWrite(RELE, LOW);
  }
  
  display.display();
}
